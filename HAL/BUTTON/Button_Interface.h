

#ifndef BUTTON_INTERFACE_H_
#define BUTTON_INTERFACE_H_

typedef enum {
	PRESSED,
	NO_PRESSED
}ButtonStatus_type;

#define PULL_UP 1 
#define EXTERNAL_PULL_DWN 3
#define BUTTON_CONNECTION_WAY  PULL_UP
void BUTTON_Init(void) ;
ButtonStatus_type BUTTON_Status(DIO_Pin_type Pin);


#endif /* BUTTON_INTERFACE_H_ */