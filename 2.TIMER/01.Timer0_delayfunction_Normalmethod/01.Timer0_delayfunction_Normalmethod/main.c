/*
 * 01.Timer0_delayfunction_Normalmethod.c
 *
 * Created: 11-10-2026 19:17:21
 * Author : Sangeeth
 */ 

/* Que) Create a delay function using Timer0 in Normal mode , Take clock frequency as 16MHz and Prescalar as 1024 */

/* Step 1 : Create a function to configure Timer0 as normal mode and configure prescalar as 1024
   Step 2 : Perform required Calculations to find number of overflow in 1 second
   Step 3 : Create Delay function 
   Step 4 : Write main()
*/
# define F_CPU 16000000   
#include <avr/io.h>
#define LED PORTB5

void timer0_config()
{
	TCCR0A &= ~((1<<WGM01)| (WGM00)) ;    // Configure timer0 in Normal mode (WGM01 = 0 and WGM00 = 0)
	TCCR0B |= ((1<<CS02) | (1<<CS00)) ;   // Configure timer0 prescalar as 1024 (CS02=1, CS01=0 and CS00=1)
}

void delay_1sec()
{
	for(uint8_t i=1 ; i<=61 ; ++i)   // In this case there are 61 overflow in 1 second
	{
		while(!(TIFR0 & (1<<TOV0)))
		{
			// Wait for overflow to occur
		}		
		TIFR0 |= (1<<TOV0) ; // Clear the overflow 		
	}
}

int main(void)
{
    timer0_config() ;
	DDRB |= (1<<DDB5) ;  // Configure PORTB pin 5 as output mode
    while (1) 
    {
		PORTB ^= (1<<LED) ;
		delay_1sec() ;
    }
}

