/*
 * KEYPAD.c
 *
 * Created: 20/09/2019 05:02:33 م
 *  Author: ali ibrahim
 */ 
#include "KEYPAD.h"

void keypad_init() {
	DDRA |= (1<<0)|(1<<1)|(1<<2)|(1<<3) ; 
	DDRA &=~(1<<4)|(1<<5)|(1<<6)|(1<<6) ;
	DIO_SetPortValue(0,0xff); //pull up col & CLR rows
}

u8 keypad_Scan()
{	int i,j ; 
	for (i=0;i<ROW;i++)
	{
		DIO_SetPinValue(0,R0,1); 
		DIO_SetPinValue(0,R1,1);
		DIO_SetPinValue(0,R2,1);
		DIO_SetPinValue(0,R3,1);
		DIO_SetPinValue(0,i,0); 
		for (j=0;j<COL;j++)
		{
			if (!DIO_GetPinValue(0,j+ROW))
			{
				while(!(PINA & (1<<j+ROW)));
				 switch (i)
				 {
					 case 0 :	if (j == 0) return 7;
								else if (j == 1) return 8;
								else if (j == 2) return 9;
								else if (j == 3) return '/';
								break;
					case 1 :
								if (j == 0) return 4;
								else if (j == 1) return 5;
								else if (j == 2) return 6;
								else if (j == 3) return '*';
								break;
					case 2 :	if (j == 0) return 1;
								else if (j == 1) return 2;
								else if (j == 2) return 3;
								else if (j == 3) return '-';
								break;
					case 3 :
								if (j == 0) return '?';
								else if (j == 1) return '0';
								else if (j == 2) return '=';
								else if (j == 3) return '+';
								break;
			     }
				 
			}
		}
	}
	return 'A';//Return 'A' if no key is pressed.
}