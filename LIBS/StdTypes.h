/*
 * StdTypes.h
 *
 * Created: 3/27/2023 4:25:24 PM
 *  Author: Amm
 */ 


#ifndef STDTYPES_H_
#define STDTYPES_H_

#define NULLPTR (void*) 0



typedef unsigned char u8;
typedef   signed char s8;

typedef unsigned short u16;
typedef   signed short s16;

typedef unsigned long u32;
typedef   signed long s32;

typedef unsigned long long  u64;
typedef   signed long long  s64;
#define  MAX_U8   ((u8)255)
#define  MIN_U8   ((u8)0)

#define  MAX_S8   ((s8)127)
#define  MIN_S8   ((s8)-128)


typedef enum{
	FALSE=0X55,
	TRUE=0X80
}Bool_t;

typedef enum{
	OK=0,
	NOK,
	OUT_OF_RANGE,
	NULL_PTR

}Error_t;





#endif /* STDTYPES_H_ */