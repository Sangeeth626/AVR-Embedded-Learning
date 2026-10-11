/*
 * 01.Timer0_delayfunction.c
 *
 * Created: 09-10-2026 22:24:42
 * Author : HP
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>


#define LED PORTB5

void timer0_init()
{
	//step 1: configure timer0 in Normal Mode
	TCCR0A &= ~((1 << WGM00) | (WGM01));
	//step 3: Delay and Prescaler value calculation
	
	/*------------------------------------CALCULATION----------------------------------------
	Clock Frequency (F_CPU): 16 MHz (16,000,000 Hz)
	Prescaler Value: 1024
	F_timer(Timer Frequency) = 16,000,000 / 1024
			= 15,625 Hz
	
	 Time period: 1 / frequency - 1 / Timer Frequency (F_timer)
				= 1 / (16,000,000 /1024)
				= 1 / 15,625
				= 0.000064
				= 64 microseconds (us)
	time taken for 1 tick is 64 us, therefore time taken for 1 overflow = time taken for 1 tick x total no of ticks
    time for 1 overflow = 64 us x 256
						= 16.384 ms (milliseconds).
	1 second = 1000 milliseconds
	there fore 1 second = 1000 / 16.384
						= 61.0351 ~ 61. 
	*/
	
	//step 3: configuring prescaler value as 1024
	TCCR0B |= ((1 << CS02) | (1 << CS00));
	
}

void delay_1sec()
{
	for(uint8_t i = 1; i <= 61; ++i)
	{
		//checking if TOV0 (overflow flag bit) is set
		while(!(TIFR0 & (1 << TOV0))); //waiting for overflow.
		
		//clearing the TOV0 using by writing 1 to it.
		TIFR0 |= (1 << TOV0); //cleared the bit.
	}
}

int main(void)
{
	timer0_init();
	DDRB |= (1 << DDB5); //configuring PORTB PIN 5 as Output.
    while (1) 
    {
		PORTB ^= (1 << LED); //toggling the LED
		delay_1sec();
    }
}

