/*
 * 05.Timer0_delayfunction_Normalmethod2.c
 *
 * Created: 16-10-2026 22:13:13
 * Author : HP
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

void timer0_normal_mode_init()
{
	//step 1: configuring timer0 in normal mode
	TCCR0A &= ~((1 << WGM00) | (WGM01));
	//step 2: calculating the value to be loaded int TCNT0 register and prescaler value
	
	/*-------------------------------------------------------Calculation-----------------------------------------------------
	F_CPU = 16,000,000 MHz : 16 x 10^6
	Prescaler value : 64 
	F_timer = F_CPU / Prescaler Value
			= 16,000,000 / 64
			= 2,50,000
			= 250 KHz
	Time Required for 1 tick = 1 / F_timer 
						     = 0.000004 seconds
							 = 4 x 10^-6
							 = 4 microseconds (us)
	
	* Target Delay : 1ms = 1000 us
	* Number of ticks required for 1ms = 1000 / 4 = 250 ticks.
	* value to be loaded into TCT0 Register : Total number of ticks - Required Ticks
											= 256 - 250
											= 6.
	
	*/
	//step 3: Load the value into TCNT0
	TCNT0 = 6;
	//step 4: choose the prescaler value of 64
	TCCR0B |= ((1 << CS01) | (1 << CS00));
	TCCR0B &= ~(1 << CS02);
}

void delay_1sec()
{
	
	for(uint16_t i = 0; i < 1000; ++i)
	{
		//loading TCT0 with 6 to start the count from 06 after each over
		TCNT0 = 6;
		//clearing the overflow flag by writing logic 1 into it.
		TIFR0 |= (1 << TOV0);
		//waiting until the overflow happens
		while(!(TIFR0) & (1 << TOV0))
		{
			// Wait for overflow
		}		
	}
	
	
}
int main(void)
{
    timer0_normal_mode_init();
	DDRB |= (1 << DDB5);
	PORTB &= ~(1 << PORTB5);
    while (1) 
    {
		PORTB ^= (1 << PORTB5);
		delay_1sec();
		
    }
}

