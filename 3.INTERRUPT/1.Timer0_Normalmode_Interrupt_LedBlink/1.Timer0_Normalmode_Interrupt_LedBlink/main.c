/*
 * 1.Timer0_Normalmode_Interrupt_LedBlink.c
 *
 * Created: 30-10-2026 13:46:41
 * Author : HP
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h> 
#include <stdint.h>

volatile uint16_t overflow_count = 0 ;

ISR(TIMER0_OVF_vect) 
{
	overflow_count++ ;             // for each 1.024ms overflow happens, therefore interrupt will be triggered
	if(overflow_count >= 977)      // after 977 overflow(ie... 977 interrupt count) , LED toggles 
	{
		PORTB ^= (1<<PORTB5) ;		
		overflow_count = 0 ;      // resetting overflow count for tracking next cycle
	}
}

void timer0_normalmode_interrupt_init()
{
	// Configure timer0 in Normal mode
	TCCR0A &= ~((1<<WGM01) | (1<<WGM00)) ;
	TCCR0B &= ~(1<<WGM02) ;
	
	TCNT0 = 0 ;   // initializing Timer/Counter register to zero
	TIFR0 |= (1<<TOV0) ;   // Pre-clearing any value inside TOV0
	
	/*---------------------------------------------- Calculation ------------------------------------------------------
	F_CPU = 16000000 Hz
	prescalar = 64
	
	F_Timer = 16000000/64 = 250000 = 250KHz
	T_timer = 1 / 250000 = 0.000004 = 4 us
	
	Time taken for one overflow = 0.000004 sec * 256 count =  0.001024 sec
	
	       1     overflow = 0.001024 sec         (For each 1.024ms interrupt will be triggered)
	1 / 0.001024 overflow = 1 sec
	976.56 overflow in 1 sec 
	~977 overflow in 1 sec
*/
		
	// Configuring prescalar to 64
	TCCR0B |= ((1<<CS01) | (1<<CS00)) ;
	TCCR0B &= ~(1<<CS02) ;
	
	TIMSK0 |= (1<<TOIE0) ;     // Overflow interrupt Enable (ie.. Local Interrupt enable)
}

void gpio()
{
	DDRB |= (1<<DDB5) ;  // Configuring DDRB pin 5 as High (output mode)
	PORTB &= ~(1<<PORTB5) ;  // Initializing LED in OFF state
}

int main(void)
{
	gpio() ;
    timer0_normalmode_interrupt_init() ;
	
	sei() ;   // Enable Global interrupt
	
    while (1) 
    {
    }
}

