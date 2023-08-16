/*
 * Utils.h
 *
 * Created: 3/27/2023 4:28:42 PM
 *  Author: Amm
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define  MAPING( X1 ,  X2 ,  Y1 ,  Y2 ,  ADC)\
((((s64)ADC-X1)*((s64)Y2 - Y1))/((s64)X2 - X1 ))+(s64)Y1 



#define  READ_BIT(reg,bit)    ((reg>>bit)&1)
#define  SET_BIT(reg,bit)     (reg=reg|(1<<bit))
#define  CLR_BIT(reg,bit)     (reg=reg&~(1<<bit))
#define  TOG_BIT(reg,bit)     (reg=reg^(1<<bit))
#define  Write_PORT(reg,data) (reg = data)
#define  WRITE_BIT(reg,bit,val)    (reg=(((reg)&~(1<<bit))|(val<<bit)))




#endif /* UTILS_H_ */