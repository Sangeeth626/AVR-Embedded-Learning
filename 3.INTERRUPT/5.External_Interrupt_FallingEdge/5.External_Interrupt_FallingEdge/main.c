/*
 * 5.External_Interrupt_FallingEdge.c
 *
 * Created: 02-11-2026 23:16:47
 * Author : HP
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT0_vect)
{
	PORTB ^= (1<<PORTB5);
}

void external_interrupt_INT0_init()
{
	EIMSK |= (1<<INT0) ; // Configuring or Enabling INT0 as Interrupt
	
	DDRD &= ~(1<<DDD6) ; // Configuring PD2 as input for external interrupt
	
	// Configuring for Falling Edge on INT0 generate an interrupt request
	EICRA |= (1<<ISC01);
	EICRA &= ~(1<<ISC00);
	
	sei() ;  // Enabling Global interrupt
}

void gpio_init()
{
	DDRB |= (1<<DDB5) ;  // Configuring DDRB Pin 5 as HIGH (output mode)
}

int main(void)
{
	gpio_init() ;
    external_interrupt_INT0_init() ;
	
    while (1) 
    {
    }
}

