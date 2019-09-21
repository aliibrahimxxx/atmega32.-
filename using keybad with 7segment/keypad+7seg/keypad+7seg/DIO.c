/*
 * DIO.c
 *
 * Created: 20/09/2019 08:03:30 م
 *  Author: ali ibrahim
 */ 
#include "DIO.h"
#include "macros.h"
volatile u8* DDR[4]={&DDRA,&DDRB,&DDRC,&DDRD};
volatile u8* PRT[4]={&PORTA,&PORTB,&PORTC,&PORTD};
volatile u8* PIN[4]={&PINA,&PINB,&PINC,&PIND};

void DIO_SetPinDirection(u8 PortNumber,u8 pinNumber,u8 direction){
	if(direction ==0){
		CLRBIT(*DDR[PortNumber],pinNumber);
	}
	else{
		SETBIT(*DDR[PortNumber],pinNumber);
	}
}
void DIO_SetPinValue(u8 PortNumber,u8 PinNumber,u8 Value){
	if (Value==0){
		CLRBIT(*PRT[PortNumber],PinNumber);
	}
	else{
		SETBIT(*PRT[PortNumber],PinNumber);
	}
}
u8   DIO_GetPinValue(u8 PortNumber,u8 PinNumber){
	return GETBIT(*PIN[PortNumber],PinNumber);
}
//-----------------------------------------------------------------------
void DIO_SetPortDirection(u8 PortNumber,u8 Direction){
	if(Direction==0){
		*DDR[PortNumber]=0x00;
	}
	else{
		*DDR[PortNumber]=0xff;
	}
}
void DIO_SetPortValue(u8 PortNumber,u8 Value){
	*PRT[PortNumber]=Value;
}
u8   DIO_GetPortValue(u8 PortNumber){
	return *PIN[PortNumber];
}
u8   DIO_SwPressed(u8 PortNumber,u8 PinNumber){
	return !(DIO_GetPinValue(PortNumber,PinNumber));
}