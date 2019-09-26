/*
 * interruptANDleds.c
 *
 * Created: 26/09/2019 01:55:04 م
 * Author : ali ibrahim
 */ 
#define F_CPU 1000000ul
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
ISR(INT0_vect){
	PORTA |=(1<<0) ; 
	_delay_ms(1000); 
}
ISR(INT1_vect){
	PORTA |=(1<<1); 
	_delay_ms(1000); 
}
ISR (INT2_vect){
	PORTA |=(1<<2);
	_delay_ms(1000); 
}
int main(void)
{	
	 cli();// SREG &= ~(1<<7); 
	 DDRA |=(1<<0)|(1<<1)|(1<<2);
	// DDRD &=~((1<<2)|(1<<3))  ; 
	 DDRB &=~(1<<2);
	 MCUCR |=(1<<0)|(1<<2)|(1<<3); 
	 MCUCR &=~(1<<1); 
	 MCUCSR &=~(1<<7);
	 DDRA |= (1<<0) ;
	 GICR |=(1<<6)|(1<<5)|(1<<7) ;
	 sei();
    while (1) 
    {
		PORTA &=~((1<<0)|(1<<1)|(1<<2));
		_delay_ms(2000) ;
    }
}

