/*
 * 03.Timer0_delayfunction_CTCmethod.c
 *
 * Created: 12-10-2026 22:25:38
 * Author : HP
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

void gpio_init()
{
	DDRB |= (1 << DDB5); //configuring PORTB Pin 5 as Output.
}
//timer0 initialization in CTC Mode
void timer0_ctc_init()
{
	//step 1: configuring timer0 in ctc mode
	TCCR0A |= (1 << WGM01);
	TCCR0A &= ~(1 << WGM00);
	
	/*---------------------------------------------------CALCULATION------------------------------------------
	Fcpu = 16,000,000
	Prescaler value = 64
	
	F_timer = 16,000,000 / 64
			= 2,50,000
			= 250 KHz
	Tick Period (T_tick) = 1 / F_timer
						 = 1 / 250 KHz
						 = 0.000004
						 = 4 microseconds = 4us
	
	Target Delay = 1 ms = 1000 us
	required ticks = (target delay / tick period) - 1
				   = (1000 / 4) - 1
				   =  250 - 1
				   = 249 ticks
	
	*/
	//step 2: configuring prescaler value as 64
	TCCR0B |= ((1 << CS01) | (1 << CS00));
	TCCR0B &= ~(1 << CS02);
	
	//step 3:  loading the calculated required ticks for 1 ms into OCR0A register.
	OCR0A = 249;
}
void delay_1sec(uint16_t ms)
{
	for(uint16_t i = 0; i < ms; ++i)
	{
		//waiting until the compare match flag A is set.
		while (!(TIFR0 & (1 << OCF0A)));
		//clearing the flag.
		TIFR0 |= (1 << OCF0A); //cleared
	}
}
int main(void)
{
	gpio_init();
	timer0_ctc_init();
	
    while (1) 
    {
		//toggling the bit in each iteration
		PORTB ^= (1 << PORTB5);
		delay_1sec(2000); 
    }
}


