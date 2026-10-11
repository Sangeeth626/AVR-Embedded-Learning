/*
 * GPIO OUTPUT.c
 *
 * Created: 29-09-2026 19:13:44
 * Author : HP
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// Making in b5 an output pin
	DDRB |= (1<<DDB5) ;
    while (1) 
    {
		PORTB |= (1<<PORTB5);   // make pin b5 = 1 
		_delay_ms(1000) ;  // 1 second delay
		PORTB &= ~(1<<PORTB5) ;  // make pin b5 = 0
		_delay_ms(1000);
    }
}

