/*
 * 04.Timer0_delayfunction_CTCmethod.c
 *
 * Created: 14-10-2026 19:54:54
 * Author : HP
 */ 

/* Que) Create a delay function using Timer 0 in CTC mode,
        Initialize the Timer/Counter register */

/* Step 1 : Configure timer 0 in CTC mode
   Step 2 : Configure prescalar value
   Step 3 : Perform calculation to find the required ticks
   Step 4 : Load Calculated required ticks for 1ms into OCRA register
   Step 5 : Create delay function
   Step 6 : Write our main function
*/

   
#define F_CPU 16000000
#include <avr/io.h>

void timer0_ctc_init()
{	
	TCCR0A &= ~((1<<WGM01) |(1<<WGM00)) ;
	TCCR0A |= (1<<WGM01) ;
	
	TCCR0B &= ~((1<<CS02) | (1<<CS01) | (1<<CS00)) ;
	TCCR0B |= (1<<CS02) ;
	
	OCR0A = 15 ;
}

/*----------------------------  Calculations  ------------------------------

F_CPU = 16MHz = 16,000,000
Prescalar value = 256

      F_timer = F_CPU / Prescalar 
	          = 16000000/256 
			  = 62500  = 65.5 KHz
			  
	  Tick period(T_tick) = 1 / F_timer
	                      = 1/62500
						  = 0.000016  = 16us
						
	  Target delay = 1ms = 1000us
	  
	  Required ticks = (Target delay / T_tick) - 1
	  				 = (1000 / 16) - 1
					 =  62.5 - 1
					 = 61.5  = approx 62 ticks
		
---------------------------------------------------------------------------------*/					 
					  	  
void delay(uint32_t ms)
{
	for(uint32_t i=0 ; i<ms ; ++i)
	{
		while(!(TIFR0 & (1<<OCF0A)))
		{
			// waiting for TCNT0 == OCF0A and then OCF0A flag of TIFR0 register become set
		}
		TIFR0 |= (1<<OCF0A) ;
	}
}
					  						  		  
int main(void)
{
    DDRB |= (1<<DDB5) ;	
	timer0_ctc_init() ;
    while (1) 
    {
		PORTB ^= (1<<PORTB5);
		delay(1000) ;
    }
}

