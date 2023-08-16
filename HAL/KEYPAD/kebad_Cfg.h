

#ifndef KEBAD_CFG_H_
#define KEBAD_CFG_H_
#define KEY_MARTIX_SIZE 4
#define KEY_ 2
#define KEY_COL 4
#define KEY_ROW 4
static DIO_Pin_type intrerface [KEY_][KEY_MARTIX_SIZE] = {
	{	DIO_PINB4, 	DIO_PINB5,	DIO_PINB6,	DIO_PINB7},
	{	DIO_PIND2, 	DIO_PIND3,	DIO_PIND4,	DIO_PIND5}
	
};
static u8 keys_ret [KEY_ROW][KEY_COL]= {
	{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'c','0','=','+'},
};



#endif /* KEBAD_CFG_H_ */