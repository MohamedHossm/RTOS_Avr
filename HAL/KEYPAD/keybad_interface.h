

#ifndef KEYBAD_INTERFACE_H_
#define KEYBAD_INTERFACE_H_
#define NO_KEY_PRESSED 'R'

#define OUTPUT_START(x) intrerface[0][(x)]
#define INPUT_START(x) intrerface[1][(x)]


	
void KEY_Init();
u8 KEY_Read_ch();



#endif /* KEYBAD_INTERFACE_H_ */