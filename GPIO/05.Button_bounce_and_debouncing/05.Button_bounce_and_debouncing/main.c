/*
 * 05.Button_bounce_and_debouncing.c
 *
 * Created: 10-10-2026 19:53:21
 * Author : HP
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRD &= ~(1<<DDD5) ;  // Setting Data Direction Register D bit 5 to LOW (input mode)
	PORTD |= (1<<PORTD5) ; // Enable internal pull up through PORT B register bit 5
	
	DDRB |= (1<<DDB5) ;   // Setting Data Direction Register B bit 5 to HIGH (output mode)
	PORTB &= ~(1<<PORTB5) ; // Making initially LED condition OFF
	
	
	while (1)
	{
		if(!(PIND & (1<<PIND5)))     // Checking button is pressed(that is PD5 is LOW)
		{
			_delay_ms(20) ;     // Lets press bounce settle
			
			if(!(PIND & (1<<PIND5)))    // Checking if PD5 is still LOW
			{
				PORTB ^= (1<<PORTB5) ;
				
				while(!(PIND & (1<<PIND5)))
				{
					// wait here until button stay pressed
				}
				
				_delay_ms(20);    // Let release bounce settle
			}
		}

	}  // exit the while(1) loop
}

