

#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "keybad_interface.h"
#include "UART.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

#define  REDLED       DIO_PINC0
#define  GREENLED     DIO_PINC1
#define  BLUENLED     DIO_PINC2
#define  RELAY1       DIO_PINC3
#define  RELAY2       DIO_PINC4
#define  BUZZER       DIO_PINC5
typedef struct {
	u8 String [30] ;
}MailBoxString;

void LED1(void *ptr);
void LED2(void *ptr);
void LCD_vDisplaykeybad(void *ptr);
void LCD_vGetkeybad(void *ptr);
void Control_functions(void *ptr);
void Uart_String_LCD(void * ptr);
void Uart_GetString_BroudCast(void * ptr );
void UartHandle_ISR(void);
// lcd semaphore for shared source protection
xSemaphoreHandle SEM_LCD ;

// Uart semaphore for synch
xSemaphoreHandle SEM_UART ;

// mail box
xQueueHandle QueueKeyPad ;

// queue for uart
xQueueHandle QueueUart ;


// queue for uart2
xQueueHandle QueueUartString ;
int main(void)
{
	DIO_Init() ;
	LCD_Init();
	KEY_Init();
	UART_Init() ;
	UART_RX_InterruptEnable();
	UART_RX_SetCallBack(&UartHandle_ISR);
	SEI();
	SEM_LCD=xSemaphoreCreateCounting(1,1);
	SEM_UART=xSemaphoreCreateCounting(1,0);

	QueueKeyPad=xQueueCreate(1,sizeof(u8));
	QueueUart=xQueueCreate(30,sizeof(u8));
	//mail Box for string
	QueueUartString = xQueueCreate(1,sizeof(MailBoxString));

	xTaskCreate(&LED1 ,NULL,50,NULL,3,NULL);
	xTaskCreate(&LED2 ,NULL,50,NULL,3,NULL);
	xTaskCreate(&LCD_vDisplaykeybad ,NULL,150,NULL,1,NULL);
	xTaskCreate(&LCD_vGetkeybad ,NULL,150,NULL,1,NULL);
	xTaskCreate(&Control_functions ,NULL,150,NULL,1,NULL);
	xTaskCreate(&Uart_String_LCD , NULL ,150 , NULL,1,NULL);
	xTaskCreate(&Uart_GetString_BroudCast , NULL ,150 , NULL,1,NULL);
	//start os 
	vTaskStartScheduler();
	while (1)
	{
	}
}

void LED1(void *ptr){
	while (1)
	{
		//TOG_BIT(PORTB,5);
		DIO_TogglePin(DIO_PINB2);
		vTaskDelay(1000);
	}
}
void LED2(void *ptr){
	while (1)
	{
		//TOG_BIT(PORTB,6);
		DIO_TogglePin(DIO_PINB1);
		vTaskDelay(2000);
	}
}
void LCD_vDisplaykeybad(void *ptr){
	u8 local_u8status = 0 ;
	u8 local_u8statuskey = 0 ;

	static u32 local_u32counter  = 0 ;
	u8 local_u8Recivedata = 0 ;
	while (1)
	{
		local_u8status = xSemaphoreTake(SEM_LCD,0xffff);
		local_u8statuskey = xQueuePeek(QueueKeyPad,&local_u8Recivedata,0x00);
		if (local_u8status==pdPASS)
		{
			if (local_u8statuskey==pdPASS){
				LCD_SetCursor(1,0);
				LCD_WriteString("key = ");
				LCD_WriteChar(local_u8Recivedata);
			}
			LCD_SetCursor(0,0);
			//LCD_WriteString("                         ");
			//LCD_SetCursor(0,0);
			LCD_WriteString("lcd works ");
			LCD_WriteNumber(local_u32counter++);
			xSemaphoreGive(SEM_LCD);
			vTaskDelay(100);
			}else {
			//do nothing
			
		}
	}
}
void LCD_vGetkeybad(void *ptr){
	u8 local_u8statuskey = 0 ;
	while (1)
	{
		local_u8statuskey =KEY_Read_ch();
		if (local_u8statuskey!=NO_KEY_PRESSED){
			xQueueOverwrite(QueueKeyPad,&local_u8statuskey);
			
			}else {
			//do nothing
			
		}
		vTaskDelay(100);
	}
}
void Control_functions (void *ptr){
	u8 local_u8Arrayselective[]= {
		REDLED  ,
		GREENLED  ,
		BLUENLED  ,
		RELAY1  ,
		RELAY2   ,
		BUZZER
	};
	u8 local_u8ReciveData = 0 ;
	u8 local_u8status = 0 ;
	while (1){
		local_u8status = xQueuePeek(QueueKeyPad,&local_u8ReciveData,0x0);
		if (local_u8status==pdPASS){
			local_u8ReciveData = local_u8ReciveData -'0';
			if (local_u8ReciveData < 6){
				for (u8 local_u8index = 0 ;local_u8index < 6 ;local_u8index++ ){
					if (local_u8index==local_u8ReciveData){
						DIO_WritePin(local_u8Arrayselective[local_u8index] , HIGH);
						}else {
						DIO_WritePin(local_u8Arrayselective[local_u8index] , LOW);
					}
				}
			}
		}
		vTaskDelay(100);
	}
}

void Uart_GetString_BroudCast(void * ptr ){
	u8 local_8ustatusSEM_UART = 0 ;

	u8 local_8ustatusQueueUart = 0 ;
	u8 local_indexconter = 0 ;
	u8 local_u8Recivetemp =0 ;
	MailBoxString  local_u8dataarray ={{0}};
	while (1)
	{
		local_8ustatusSEM_UART = xSemaphoreTake(SEM_UART,0);
		if (local_8ustatusSEM_UART== pdPASS){
			local_8ustatusQueueUart = xQueueReceive(QueueUart,&local_u8Recivetemp,0);
			while(local_8ustatusQueueUart==pdPASS){
				local_u8dataarray.String[local_indexconter++] = local_u8Recivetemp ;
				local_8ustatusQueueUart = xQueueReceive(QueueUart,&local_u8Recivetemp,0);
			}
			local_u8dataarray.String[local_indexconter-1] = 0  ;
			local_indexconter = 0 ;
			xQueueOverwrite(QueueUartString,&local_u8dataarray);
			}else {
			//do nothing
		}
	vTaskDelay(100);
	}
}

void Uart_String_LCD(void * ptr){
	u8 local_8ustatusSEM_LCD = 0 ;
	MailBoxString local_data = {{0}} ;
	while(1){
		local_8ustatusSEM_LCD = xSemaphoreTake(SEM_LCD,0);
		xQueuePeek(QueueUartString,&local_data,0);
		if  (local_8ustatusSEM_LCD==pdPASS){
			LCD_SetCursor(1,8);
			LCD_WriteString("     ");
			LCD_SetCursor(1,8);
			LCD_WriteString((char*)local_data.String);
			LCD_WriteString("             ");
			xSemaphoreGive(SEM_LCD);
			}else {
			//do nothing
		}
		vTaskDelay(100);
	}
}
void UartHandle_ISR(){
	
	u8 local_u8dataRecive = 0 ;
	u8 local_u8status = 0 ;
	local_u8dataRecive = UART_ReceiveNoBlock() ;
	if (local_u8dataRecive == '#'){
		xSemaphoreGiveFromISR(SEM_UART,0);
	}
	local_u8status = xQueueSendFromISR(QueueUart,&local_u8dataRecive,0);
	if (local_u8status!=pdPASS){
		xSemaphoreGiveFromISR(SEM_UART,0);
		}else{
		//do nothing
	}
}