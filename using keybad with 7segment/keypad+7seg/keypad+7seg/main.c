/*
 * keypad+7seg.c
 *
 * Created: 19/09/2019 08:35:45 م
 * Author : ali ibrahim
 */ 



#include "KEYPAD.h"
#include "macros.h"
#include "xdelay.h"


int main(void)
{ u8 key = 0  ;
	keypad_init();
	DDRC |= (1<<0)|(1<<1)|(1<<2)|(1<<3);
	PORTC = key ;
    while (1) 
    { 
		key =  keypad_Scan() ; 
		if(key!='A'){
			PORTC = key; }
    }
}

