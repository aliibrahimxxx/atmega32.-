/*
 * xdelay.h
 *
 * Created: 20/09/2019 07:21:36 م
 *  Author: ali ibrahim
 */ 


#ifndef XDELAY_H_
#define XDELAY_H_
#include "DATA_TYPES.h"
/* 1Mhz means that it does 1000000 cycles in 1 sec 
so 1 cycle take 1/1000000 sec which is equal to 1us 
so it means to have a delay_ms(1000) which mean number of cycles = (1000000/1000)*1000 = 1000000 cycle = 1 sec */

#define clock 1000000 
 static float count ; 
 #define delay_MS(x)\
		 for (count=0;count<(clock/1000)*x;count++)	\
		 {	\
			_asm("NOP");	\ 
		 }	\

#endif /* XDELAY_H_ */