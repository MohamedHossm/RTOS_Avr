 


 #ifndef LCD_CFG_H_
 #define LCD_CFG_H_

 // _4_bit
 //_8_bit

 #define LCD_CONF _4_bit

 #define RS  DIO_PINA1
 #define EN  DIO_PINA2
 
/*
 #define RS  DIO_PINC1
 #define EN  DIO_PINC0
*/
 #define D7  DIO_PINA6
 #define D6  DIO_PINA5
 #define D5  DIO_PINA4
 #define D4  DIO_PINA3
/*
  #define D4  DIO_PINA0
  #define D5  DIO_PINA1
  #define D6  DIO_PINA2
  #define D7  DIO_PINA3
  */
 #endif /* LCD_CFG_H_ */