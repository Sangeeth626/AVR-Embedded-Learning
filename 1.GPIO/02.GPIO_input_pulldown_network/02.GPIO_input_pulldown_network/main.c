/*
 * 02.GPIO_input_pulldown_network.c
 *
 * Created: 09-10-2026 17:04:31
 * Author : HP
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD &= ~(1<<DDD4) ;  // Setting Data Direction Register Bit 5 to LOW (input mode)
    DDRB |= (1<<DDB5);   // Setting Data Direction Register Bit 5 to HIGH (output mode)
	
    while(1) 
    {	// Checking PINB register for switch press
		if((PIND & (1<<PIND4)))
		{
			PORTB |= (1<<PORTB5);    // LED ON
        }
		else
		{
			PORTB &= ~(1<<PORTB5) ;  // LED OFF
		}
	}
}

