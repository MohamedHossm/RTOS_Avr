/*
 * LCD_Private.h
 *
 * Created: 3/31/2023 9:18:19 PM
 *  Author: Amm
 */ 


#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

#define _4_bit 0 
#define _8_bit 1

static void WriteData (u8 data );
static void WriteInst (u8 inst );
	/*
	u8 Human[] = {
	0x0A,
	0x0E,
	0x04,
	0x0E,
	0x15,
	0x0A,
	0x11,
	0x00
	};
	u8 arrow[] = {
	0x00,
	0x04,
	0x06,
	0x1F,
	0x06,
	0x04,
	0x00,
	0x00
	};
	u8 rep[]={
	0x04,
	0x0E,
	0x0E,
	0x1F,
	0x0E,
	0x1F,
	0x1F,
	0x00
	};

	*/
#endif /* LCD_PRIVATE_H_ */