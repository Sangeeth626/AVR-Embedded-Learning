/*
 * 06.DC_motor_CW_and_ACW_rotation.c
 *
 * Created: 19-10-2026 13:42:10
 * Author : HP
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <stdint.h>  // uint16_t is from this library

void timer0_ctc_init()
{
	TCCR0A &= ~((1<<WGM00) | (1<<WGM01)) ;
	TCCR0A |= (1<<WGM01) ;
	
	TCNT0 = 0 ;         // Counter start from zero
	OCR0A = 249 ;       // Here 250 count * 4us = 1ms
	
	TIFR0 = (1<<OCF0A) // Clear any pending compare-match flag
	
	TCCR0B &= ~((1<<CS02) | (1<<CS01) | (1<<CS00)) ;
	TCCR0B |= (1<<CS01) | (1<<CS00) ;
}

void delay(uint16_t ms)
{
	for(uint16_t i=0 ; i< ms ; i++)
	{
		while(!(TIFR0 & (1<<OCF0A)))
		{
			// Waiting for TCNT0 == OCR0A (ie.. waiting for OCF0A flag to set)
			// TIFR0 flag register become 1 when TCNT0 become 249 which is equal to the OCR0A, For each loop TCNT0 increments 0->1->2......->248->249 loop exit 
		}
		TIFR0 = (1<<OCF0A) ;
	}
}

void dc_motor_init()
{
	DDRD |= (1<<DDD1)| (1<<DDD2) | (1<<DDD3) ; // Configured Direction of PORTD pin 1,2 and 3 to HIGH (Output mode).	
	
	PORTD |= (1<<PORTD3) ;   // Setting PORTD3 to HIGH ( note : Enable pin should stay HIGH)
}

void forward_rotation()
{
	// Forward Rotation
	PORTD |= (1<<PORTD1) ;
	PORTD &= ~(1<<PORTD2) ;
}

void backward_rotation()
{
	// Backward Rotation
	PORTD &= ~(1<<PORTD1);
	PORTD |= (1<<PORTD2) ;
}

void stop_rotation()
{
	// Stop Rotation
	PORTD &= ~((1<<PORTD1) | (1<<PORTD2)) ;
}

int main(void)
{
    dc_motor_init() ;
	timer0_ctc_init() ;
	
    while (1) 
    {
		forward_rotation() ;
		delay(3000);
		
		stop_rotation() ;
		delay(1000);
		
		backward_rotation() ;
		delay(3000);
    }
}

