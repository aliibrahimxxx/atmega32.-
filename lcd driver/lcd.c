/*
 * lcd.c
 *
 * Created: 21/09/2019 07:02:27 م
 *  Author: ali ibrahim
 */
#include <stdio.h> 
#include <stdlib.h>
#include "lcd.h"
#include "DATA_TYPES.h"
#include <util/delay.h>
void LCD_lcd_init(void)
{

	_delay_ms(20);
	lcd_ctr_direction |= (1<<en_switch | 1<<rw_switch | 1<<rs_switch) ;
	lcd_ctr &= ~(1<<en_switch | 1<<rw_switch | 1<<rs_switch) ;
	lcd_data_port_direction |= (1<<d0)|(1<<d1)|(1<<d2)|(1<<d3)|(1<<d4)|(1<<d5)|(1<<d6)|(1<<d7) ;
	lcd_data_port_direction = 0xff;
	_delay_ms(15);

	LCD_clear_screen ();

	#ifdef EIGHT_BIT_MODE
	LCD_Send_A_Command(LCD_FUNCTION_8BIT_2LINES);

	#endif
	#ifdef FOUR_BIT_MODE
	LCD_Send_A_Command(0x02);

	LCD_Send_A_Command(LCD_FUNCTION_4BIT_2LINES);

	#endif

	LCD_Send_A_Command(LCD_ENTRY_MODE);
	LCD_Send_A_Command(LCD_BEGIN_AT_FIRST_RAW);
	LCD_Send_A_Command(LCD_DISP_ON_CURSOR_BLINK);

}
void LCD_clear_screen ()
{
	LCD_Send_A_Command(LCD_CLEAR_SCREEN); // clear the screen

}
void LCD_GotoXY(u8 line, u8 position )
{

	if(line==0)
	{
		if (position < 16 && position >=0)
		LCD_Send_A_Command(0x80+position);
	}
	else if (line==1)
	{
		if (position < 16 && position >=0)
		LCD_Send_A_Command(0xc0 + position);
	}
}

void LCD_check_lcd_isbusy()
{
	lcd_data_port_direction &= ~((1<<d0)|(1<<d1)|(1<<d2)|(1<<d3)) ;
	lcd_ctr |= (1<<rw_switch); // read
	lcd_ctr &= ~ (1<<rs_switch);

		//while (GETBIT(lcd_data_port,d7))
	//	{
	LCD_lcd_kick ();
	//	}

	//	_delay_ms (500) ;
	lcd_data_port_direction = 0xFF; //0xFF means 0b11111111
	lcd_data_port &= ~ (1<<rw_switch); //write
}

void LCD_Send_A_Command_4mode(u8 command)
{
	LCD_check_lcd_isbusy();
	lcd_data_port&= 0x0F;
	lcd_data_port |= (command&0xF0);
	lcd_ctr &= ~ ((1<<rw_switch)|(1<<rs_switch));
	LCD_lcd_kick ();
	lcd_ctr &= 0x0F;  // Make Data Nibble as 0000
	lcd_ctr |= ((command<<4)&0xF0);
	LCD_lcd_kick ();
	//LCD_port = 0;
}



void LCD_Send_A_Character(u8 character)
{

	#ifdef EIGHT_BIT_MODE
	LCD_check_lcd_isbusy();

	lcd_ctr |= 1<<rs_switch; //turn RS ON for Data mode.
	lcd_data_port = ( ( (character  ) << 0)   )  ;
	lcd_ctr |= 1<<rs_switch; //turn RS ON for Data mode.
	lcd_ctr &= ~ (1<<rw_switch);//turn RW off so you can write.


	LCD_lcd_kick ();
	//LCD_port = 0;
	#endif
	
	
	#ifdef FOUR_BIT_MODE
	lcd_data_port = (lcd_data_port & 0x0F) | (character & 0xF0);
	lcd_ctr |= 1<<rs_switch; //turn RS ON for Data mode.
	lcd_ctr &= ~ (1<<rw_switch);//turn RW off so you can write.
	LCD_lcd_kick ();
	lcd_data_port = (lcd_data_port & 0x0F) | (character << 4);
	lcd_ctr |= 1<<rs_switch; //turn RS ON for Data mode.
	lcd_ctr &= ~ (1<<rw_switch);//turn RW off so you can write.
	LCD_lcd_kick ();

	#endif


}

void LCD_Send_A_String(char *StringOfCharacters)
{


	int count=0 ;//to count how much char on the line (it should be 16 char only)
	while(*StringOfCharacters > 0)
	{
		count++;
		LCD_Send_A_Character(*StringOfCharacters++);
		if (count == 16  ) // go to the second line
		{
			LCD_GotoXY(1,0); //line 1 position zero
		}
		else if (count == 32 || count==33) // clear screen and show again
		{
			LCD_clear_screen();
			LCD_GotoXY(0,0); //line 0 position zero
			count = 0 ;
		}
	}
}


void LCD_display_number (int Number )
{

	u8  str[4];

	sprintf(str,"%d",Number);	// Adjust the formatting to your liking.

	LCD_Send_A_String (str) ;

}

void LCD_display_real_number (double  Number )
{

	u8  str[16];


	char *tmpSign = (Number < 0) ? "-" : "";
	float tmpVal = (Number < 0) ? -Number : Number;

	int tmpInt1 = tmpVal;                  // Get the integer (678).
	float tmpFrac = tmpVal - tmpInt1;      // Get fraction (0.0123).
	int tmpInt2 = tmpFrac * 10000;  // Turn into integer (123).

	// Print as parts, note that you need 0-padding for fractional bit.

	sprintf (str, "%s%d.%04d", tmpSign, tmpInt1, tmpInt2);

	LCD_Send_A_String (str) ;

}

void LCD_lcd_kick ()
	{
		lcd_ctr &= ~ (1<<en_switch);
		asm volatile ("nop");
		asm volatile ("nop");
		_delay_ms (50) ;
		lcd_ctr |= 1<<en_switch;
	}
void LCD_Send_A_Command(unsigned char command)
{
	#ifdef EIGHT_BIT_MODE
	LCD_check_lcd_isbusy();

	lcd_data_port = command  ;
	lcd_ctr &= ~ ((1<<rw_switch)|(1<<rs_switch));
	LCD_lcd_kick ();
	//LCD_port = 0;
	#endif
	#ifdef FOUR_BIT_MODE
	LCD_check_lcd_isbusy();
	lcd_data_port = (lcd_data_port & 0x0F) | (command & 0xF0);
	//LCD_VoidLcd_waitIfBusy();
	//SET_DATA_DIRECTION_REGISTER(LCD_DATA_DIRECTION_PORT, PORT_OUTPUT_DIRECTION);
	//LCD_SET_REGISTER_SELECT(LCD_REGISTER_SELECT_DISABLE);
	//	LCD_SET_READ_WRITE(WRITE_TO_LCD);
	lcd_ctr &= ~ ((1<<rw_switch)|(1<<rs_switch));
	//LCD_VoidLcd_referish();
	LCD_lcd_kick ();
	lcd_data_port = (lcd_data_port & 0x0F) | (command << 4);
	//LCD_VoidLcd_waitIfBusy();
	lcd_ctr &= ~ ((1<<rw_switch)|(1<<rs_switch));
	//LCD_VoidLcd_referish();
	LCD_lcd_kick ();
	#endif

}

