

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


void LCD_Init(void);

void LCD_WriteChar(u8 ch);
void LCD_WriteString(char *str );
void LCD_WriteNumber(s64 num);
void LCD_WriteBinary(u8 num);
void LCD_WriteHex(u8 num);
void LCD_SetCursor(u8 line,u8 cell);
void LCD_Clear(void);
void LCD_SetFiguer(u8* data,u8 pos );
void LCD_WriteNumber2(long num);
void LCD_Reuse  (u8 *data , u8 ram, u8 line , u8 cell  );
void Draw_LCD_Circ(u8 * sring , u16 pos);





#endif /* LCD_INTERFACE_H_ */