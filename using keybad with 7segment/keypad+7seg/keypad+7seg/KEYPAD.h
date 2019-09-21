/*
 * KEYPAD.h
 *
 * Created: 20/09/2019 04:08:56 م
 *  Author: ali ibrahim
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "DATA_TYPES.h" 
#include "REG.h"
#include "DIO.h"
#define PORT PORTA 
#define ROW 4 
#define COL 4
//----------------------------
#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7

void keypad_init() ; 
u8   keypad_Scan(); 





#endif /* KEYPAD_H_ */