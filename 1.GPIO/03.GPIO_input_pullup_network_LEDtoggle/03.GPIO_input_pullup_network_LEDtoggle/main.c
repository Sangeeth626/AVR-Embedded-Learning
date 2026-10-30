/*
 * 03.GPIO_input_pullup_network_LEDtoggle.c
 *
 * Created: 09-10-2026 20:06:04
 * Author : HP
 */ 
#define F_CPU 16000000
#include <avr/io.h>


int main(void)
{
    DDRD &= ~(1<<DDD5) ; // Set Data Direction Register D Bit 5 to input mode
	DDRB |= (1<<DDB5) ; // Set Data Direction Register B Bit 5 to output mode
	
    while(1) 
    {
		if((PIND & (1<<PIND5)))
		{
			PORTB |= (1<<PORTB5) ;
		}
		else
		{
			PORTB &= ~(1<<PORTD5) ;
		}
	}
	
		
			
// Another Way 
	/*while(1)
	{
		if(!(PIND & (1<<PIND5)))
		{
			PORTB ^= (1<<PORTB5) ;
		}
    }*/
}

