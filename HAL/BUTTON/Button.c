#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "DIO_Interface.h"
#include "Button_Interface.h"
#include "Button_Cfg.h"
void BUTTON_Init(void){
	/* do noting */
}

ButtonStatus_type BUTTON_Status2(DIO_Pin_type pin){
	
	ButtonStatus_type ret = NO_PRESSED ;
	
	DIO_Port_type port = pin / PORT_SIZE ;
	u8 pin_num = pin % PORT_SIZE ;
	switch(port)
	{
		case PA:
		if (READ_BIT(DDRA,pin_num)==LOW && READ_BIT(PORTA,pin_num)==HIGH){
			if(READ_BIT(PINA,pin_num)==LOW){
				ret = PRESSED  ;
				}else{
				ret = NO_PRESSED  ;
			}
		}
		else if (READ_BIT(DDRA,pin_num)==LOW && READ_BIT(PORTA,pin_num)==LOW){
			if(READ_BIT(PINA,pin_num)==HIGH){
				ret = PRESSED  ;
				}else{
				ret = NO_PRESSED  ;
			}
		}
		break;
		
		case PB:
		if (READ_BIT(DDRB,pin_num)==LOW && READ_BIT(PORTB,pin_num)==HIGH){
			if(READ_BIT(PINB,pin_num)==LOW){
				ret = PRESSED  ;
				}else{
				ret = NO_PRESSED  ;
			}
		}
		else if (READ_BIT(DDRB,pin_num)==LOW && READ_BIT(PORTB,pin_num)==LOW){
			if(READ_BIT(PINB,pin_num)==HIGH){
				ret = PRESSED  ;
				}else{
				ret = NO_PRESSED  ;
			}
		}
		break;
		
		case PC:
		if (READ_BIT(DDRC,pin_num)==LOW && READ_BIT(PORTC,pin_num)==HIGH){
			if(READ_BIT(PINC,pin_num)==LOW){
				ret = PRESSED  ;
				}else{
				ret = NO_PRESSED  ;
			}
		}
		else if (READ_BIT(DDRC,pin_num)==LOW && READ_BIT(PORTC,pin_num)==LOW){
			if(READ_BIT(PINC,pin_num)==HIGH){
				ret = PRESSED  ;
				}else{
				ret = NO_PRESSED  ;
			}
		}
		break;
		
		case PD:
		if (READ_BIT(DDRD,pin_num)==LOW && READ_BIT(PORTD,pin_num)==HIGH){
			if(READ_BIT(PIND,pin_num)==LOW){
				ret = PRESSED  ;
				}else{
				ret = NO_PRESSED  ;
			}
		}
		else if (READ_BIT(DDRD,pin_num)==LOW && READ_BIT(PORTD,pin_num)==LOW){
			if(READ_BIT(PIND,pin_num)==HIGH){
				ret = PRESSED  ;
				}else{
				ret = NO_PRESSED  ;
			}
		}
		break;
	}
	return ret ;
}
ButtonStatus_type BUTTON_Status(DIO_Pin_type pin){

	ButtonStatus_type ret = NO_PRESSED ;
	DIO_Port_type port = pin / PORT_SIZE ;
	u8 pin_num = pin % PORT_SIZE ;
	#if BUTTON_CONNECTION_WAY == PULL_UP
	switch (port){
	case PA:
	if(READ_BIT(PINA,pin_num)==LOW){
		ret = PRESSED  ;
		}else{
		ret = NO_PRESSED  ;
	}
	break ;
	case PB:
	if(READ_BIT(PINB,pin_num)==LOW){
		ret = PRESSED  ;
		}else{
		ret = NO_PRESSED  ;
	}
	break;
	case PC:
	if(READ_BIT(PINC,pin_num)==LOW){
		ret = PRESSED  ;
		}else{
		ret = NO_PRESSED  ;
	}
	break;
	case PD:
	if(READ_BIT(PIND,pin_num)==LOW){
		ret = PRESSED  ;
		}else{
		ret = NO_PRESSED  ;
	}
	break;
}

#elif BUTTON_CONNECTION_WAY == EXTERNAL_PULL_DWN
switch (port){
	case PA:
	if(READ_BIT(PINA,pin_num)==HIGH){
		ret = PRESSED  ;
		}else{
		ret = NO_PRESSED  ;
	}
	break ;
	case PB:
	if(READ_BIT(PINB,pin_num)==HIGH){
		ret = PRESSED  ;
		}else{
		ret = NO_PRESSED  ;
	}
	break;
	case PC:
	if(READ_BIT(PINC,pin_num)==HIGH){
		ret = PRESSED  ;
		}else{
		ret = NO_PRESSED  ;
	}
	break;
	case PD:
	if(READ_BIT(PIND,pin_num)==HIGH){
		ret = PRESSED  ;
		}else{
		ret = NO_PRESSED  ;
	}
	break;
}
#endif
return ret ;	
}