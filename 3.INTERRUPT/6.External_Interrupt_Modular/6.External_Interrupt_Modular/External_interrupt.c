/*
 * External_interrupt.c
 *
 * Created: 04-11-2026 22:21:54
 *  Author: HP
 */ 

#include "External_interrupt.h"
#include <avr/interrupt.h>

ISR(INT0_vect)
{
	// Toggle led when pressed
	PORTB ^= (1 << PORTB5);
}


void external_interrupt_INT0_init()
{
	//step 1: configuring/ Enabling INT0 as interrupt
	EIMSK |= (1 << INT0);
	//step 2: configuring PD2 as input for  external interrupt
	DDRD &= ~(1 << DDD2);
	//step 3:Enabling Internal Pull-up
	PORTD |= (1<<PORTD2) ;
	//step 4: configuring interrupt trigger: falling edge
	EICRA |= (1 << ISC01);
	EICRA &= ~(1<<ISC00) ;
	//step 5: enabling global interrupt
	sei();
}