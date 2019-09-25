/*
 * lcd.h
 *
 * Created: 21/09/2019 06:31:24 م
 *  Author: ali ibrahim
 */ 


#ifndef LCD_H_
#define LCD_H_
#include "REG.h"
#include "DATA_TYPES.h"
#include "macros.h"
#include <util/delay.h>


#define lcd_data_port PORTD 
#define lcd_data_port_direction DDRD
#define lcd_ctr		PORTB
#define lcd_ctr_direction DDRB
#define ENABLE 1 
#define DISABLE 0 
#define READ 1
#define WRITE 0
#define DATA 1 
#define COMMAND 0 
#define rs_switch 2
#define rw_switch 1 
#define en_switch 0

#define d0 0 
#define d1 1
#define d2 2 
#define d3 3
#define d4 4 
#define d5 5
#define d6 6
#define d7 7 

#define 	EIGHT_BIT_MODE

#define LCD_FIRST_LINE								(0)
#define LCD_SECOND_LINE								(1)
#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_RAW						(0x80)
#define LCD_BEGIN_AT_SECOND_RAW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)


void LCD_check_lcd_isbusy(void);
void LCD_lcd_kick (void);
void LCD_Send_A_Command(unsigned char command);
void LCD_Send_A_Character(unsigned char character);
void LCD_Send_A_String(char *string);
void LCD_lcd_init(void);
void LCD_clear_screen ();
void LCD_GotoXY(unsigned char line, unsigned char position );
void LCD_display_number (int Number );
void LCD_display_real_number (double  Number );
void LCD_Send_A_Command_4mode(u8 command);



#endif /* LCD_H_ */