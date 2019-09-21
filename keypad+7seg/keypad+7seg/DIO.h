/*
 * DPIO.h
 *
 * Created: 20/09/2019 07:56:15 م
 *  Author: ali ibrahim
 */ 


#ifndef DIO_H_
#define DIO_H_
#include "DATA_TYPES.h"
#include "macros.h"
#include "REG.h"
void DIO_SetPinDirection(u8 PortNumber,u8 pinNumber,u8 direction);
void DIO_SetPinValue(u8 PortNumber,u8 PinNumber,u8 Value);
u8  DIO_GetPinValue(u8 PortNumber,u8 PinNumber);
void DIO_SetPortDirection(u8 PortNumber,u8 Direction);
void DIO_SetPortValue(u8 PortNumber,u8 Value);
u8  DIO_GetPortValue(u8 PortNumber);
//=======================================
u8 DIO_SwPressed(u8 PortNumber,u8 PinNumber);



#endif /* DPIO_H_ */