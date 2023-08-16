
#include "StdTypes.h"

#include "DIO_Interface.h"
#include "Button_Interface.h"
#include "keybad_interface.h"
#include "kebad_Cfg.h"
void KEY_Init(){
	/*do noting */
	for(int i = 0 ; i < KEY_MARTIX_SIZE ; i ++ ){
		DIO_WritePin(OUTPUT_START(i) , HIGH) ;
	}
}
u8 KEY_Read_ch(){
	u8 key = NO_KEY_PRESSED ;
	for (u8 i = 0 ; i < KEY_ROW ; i++ ){
		DIO_WritePin(OUTPUT_START(i) , LOW) ;
		for (u8 j = 0 ; j < KEY_COL ; j++ ){
			if (BUTTON_Status(INPUT_START(j))==PRESSED){
				while(BUTTON_Status(INPUT_START(j))==PRESSED) ;
				key = keys_ret[i][j] ;
			}
		}
		DIO_WritePin(OUTPUT_START(i) , HIGH) ;
	}
	return key ;
	
}