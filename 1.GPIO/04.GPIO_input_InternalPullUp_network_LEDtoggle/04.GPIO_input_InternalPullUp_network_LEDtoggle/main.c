/*
 * 04.GPIO_input_InternalPullUp_network_LEDtoggle.c
 *
 * Created: 10-10-2026 15:19:04
 * Author : HP
 */ 

#define F_CPU 16000000
#include <avr/io.h>

int main(void)
{
	DDRD &= ~(1<<DDD5) ;  // Setting Data Direction Register D bit 5 to LOW (Input mode)
	DDRB |= (1<<DDB5) ;   // Setting Data Direction Register B bit 5 to HIGH (Output mode)
	
	PORTD |= (1<<PORTD5) ;  // Enabling the input with internal pull-up
	
	while (1)
	{
		if(!(PIND & (1<<PIND5)))
		{
			PORTB |= (1<<PORTB5) ;
		}
		else
		{
			PORTB &= ~(1<<PORTB5) ;
		}
	}
}