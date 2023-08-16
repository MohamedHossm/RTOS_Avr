#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"


#define  F_CPU 8000000
#include <util/delay.h>

#include "LCD_Private.h"
#include "LCD_Interface.h"
#include "LCD_Cfg.h"
#include <string.h>


#if LCD_CONF == _4_bit

void LCD_Init(void){
	_delay_ms(50) ;
	WriteInst(0x02) ;
	WriteInst(0x28) ;
	WriteInst(0x0c) ; // 0x0f 0x 0e 0x0c
	WriteInst(0x01) ; //cls
	_delay_ms(1) ;
	WriteInst(0x06) ; // increase ddram no shift
}
static void WriteData (u8 data ){
	DIO_WritePin(RS , HIGH);
	
	DIO_WritePin(D7 , READ_BIT(data ,7 ));
	DIO_WritePin(D6 , READ_BIT(data ,6 ));
	DIO_WritePin(D5 , READ_BIT(data ,5 ));
	DIO_WritePin(D4 , READ_BIT(data ,4 ));
	
	DIO_WritePin(EN , HIGH);
	_delay_ms(1) ;
	DIO_WritePin(EN , LOW );
	
	DIO_WritePin(D7 , READ_BIT(data ,3 ));
	DIO_WritePin(D6 , READ_BIT(data ,2 ));
	DIO_WritePin(D5 , READ_BIT(data ,1 ));
	DIO_WritePin(D4 , READ_BIT(data ,0 ));
	
	DIO_WritePin(EN , HIGH);
	_delay_ms(1) ;
	DIO_WritePin(EN , LOW );
	_delay_ms(1) ;
}

static void WriteInst (u8 inst ){
	DIO_WritePin(RS , LOW);
	
	DIO_WritePin(D7 , READ_BIT(inst ,7 ));
	DIO_WritePin(D6 , READ_BIT(inst ,6 ));
	DIO_WritePin(D5 , READ_BIT(inst ,5 ));
	DIO_WritePin(D4 , READ_BIT(inst ,4 ));
	
	DIO_WritePin(EN , HIGH);
	_delay_ms(1) ;
	DIO_WritePin(EN , LOW );
	
	DIO_WritePin(D7 , READ_BIT(inst ,3 ));
	DIO_WritePin(D6 , READ_BIT(inst ,2 ));
	DIO_WritePin(D5 , READ_BIT(inst ,1 ));
	DIO_WritePin(D4 , READ_BIT(inst ,0 ));
	
	DIO_WritePin(EN , HIGH);
	_delay_ms(1) ;
	DIO_WritePin(EN , LOW );
	_delay_ms(1) ;
}
#endif


void LCD_WriteChar(u8 ch){
	WriteData(ch) ;
}
void LCD_Clear(void){
	WriteInst(0x01);
	_delay_ms(1);
}
void LCD_WriteString(char *str ){
	for (int i = 0 ; str[i] ; i ++ ){
		LCD_WriteChar((u8)str[i]) ;
	}
}

void LCD_WriteNumber(s64 num){
	if (num == 0 ) LCD_WriteChar('0') ; 
	if (num <  0 ){
		LCD_WriteChar('-') ;
		num = num*-1 ; 
		} 
	u8 arr[20] = {0} ;
	int i = 0 ;
	for ( ; num ; i++ ){
		arr[i] = num%10 ;
		num	 = num /10 ;
	}

	while(i--){
		LCD_WriteChar(arr[i]+'0');

	}
}
void LCD_SetCursor(u8 line,u8 cell){
	
	if (line == 0  ){
		WriteInst(0x80|cell);
	}
	else if (line ==1  ){
		WriteInst(0x80|(cell+0x40));
	}
}
void LCD_SetFiguer(u8* data,u8 pos ){
	// ser cgram
	//write data
	//set ddram
	WriteInst(0x40|(pos*8));
	for (int i = 0 ; i < 8 ; i++ ){
		WriteData(data[i]);
	}
	LCD_SetCursor(0,0);
}
void LCD_WriteBinary(u8 num){
	u8 size = sizeof(num)*8 ;
	for (int i = 0 ; i < size ; i ++ ){
		LCD_WriteChar(READ_BIT(num ,((size-1)-i))+'0');
	}
	
}
void LCD_WriteHex(u8 num){
	u8 high = num>>4 ;
	u8 low = num&0x0f ;
	
	if (high<10){
		LCD_WriteNumber(high) ;
		}else {
		LCD_WriteChar(high+55) ;
	}
	if (low<10){
		LCD_WriteNumber(low) ;
		}else {
		LCD_WriteChar(low+55) ;
	}
}
void LCD_Reuse  (u8 *data , u8 ram, u8 line , u8 cell  ){
	LCD_SetFiguer(data,ram ) ;
	LCD_SetCursor(line,cell);
	LCD_WriteChar(ram) ;
	_delay_ms(50) ;
	LCD_SetCursor(line,cell);
	LCD_WriteChar(' ') ;
	_delay_ms(1) ;
}
void Draw_LCD_Circ(u8 * sring , u16 pos){
	u8 len = strlen((char*)sring) ;
	u8 line = 0 ;
	u8 pos_pff = 0 ;
	
	for (u8 i = 0  ;  i < len ; i++ ){
		pos_pff = (pos-i)%32 ;
		line = 0 ;
		if (pos_pff >= 16 && pos_pff <= 32) {
			line = 1 ;
			LCD_SetCursor(line,pos_pff%16);
			
			} else  {
			LCD_SetCursor(line,pos_pff) ;
			
		}
		if (pos <pos_pff)continue ;
		
		LCD_WriteChar(sring[len-i-1]);
	}
}


void fun_SHuman_dead(u8 *str  ) {
		//LCD_SetFiguer(Human , 0);
		//LCD_SetFiguer(arrow , 1);
		//LCD_SetFiguer(rep , 2);
	int x = 1 ;
	while(x<18){
		if (x <15)
		{
			LCD_SetCursor(0,0);
			LCD_WriteChar(0);
			LCD_SetCursor(0,15);
			LCD_WriteChar(0);
			LCD_SetCursor(0,x);
			LCD_WriteChar(1);
			_delay_ms(200);
			LCD_SetCursor(0,x);
			LCD_WriteChar(' ');
			x++ ;
		}
		
		
		else if (x==15){
			for(int i = 0 ; i < 5 ; i ++ )
			{	LCD_SetCursor(0,15);
				LCD_WriteChar(' ');
				_delay_ms(300);
				LCD_SetCursor(0,15);
				LCD_WriteChar(0);
				_delay_ms(300);
			}
			x++ ;
		}
		else {
			LCD_SetCursor(0,15);
			LCD_WriteChar(2);
			LCD_SetCursor(1,3);
			LCD_WriteString((char*)str);
			_delay_ms(1000);
			x++ ;
		}
	}
	//LCD_WriteNumber(x++) ;

}
void LCD_WriteNumber2(long num)
{
	char   arr_num[10]= {'0','1','2','3','4','5','6','7','8','9'};
	long  arr_base10[]= {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};

	long digit,i,j;
	long devision_factor,num_copy ;
	num_copy=num;
	for (i=0; num_copy>=10; i++)
	{
		num_copy=num_copy/10;
	}
	devision_factor=arr_base10[i];
	for (j=devision_factor; j>0; j=j/10)
	{
		digit=(num/j);
		LCD_WriteChar(arr_num[digit]);
		num=(num%j);

	}


}