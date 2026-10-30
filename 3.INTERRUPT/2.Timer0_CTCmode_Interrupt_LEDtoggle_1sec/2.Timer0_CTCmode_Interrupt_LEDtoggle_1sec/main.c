/*
 * 2.Timer0_CTCmode_Interrupt_LEDtoggle_1sec.c
 *
 * Created: 30-10-2026 17:10:38
 * Author : HP
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile uint16_t overflow_count = 0 ;

ISR(TIMER0_COMPA_vect)
{ 
	overflow_count++ ;               // After each 1ms TCNT0 become 249 , Therefore interrupt will be triggered
	if(overflow_count >= 1000)       // After 1000 compare-match cycle (ie.. 1000 interrupt trigger count , LED toggle)
	{
		PORTB ^= (1<<PORTB5) ;
		overflow_count = 0 ;     // Resetting Overflow count for tracking next cycle
	}
}


void timer0_CTCmode_interrupt_1sec()
{
	// Configure timer0 in CTC mode
	TCCR0A |= (1<<WGM01) ;
	TCCR0A &= ~(1<<WGM00) ;
	TCCR0B &= ~(1<<WGM02) ;
	
	TCNT0 = 0 ;    // Initializing TCNT0 to zero
	TIFR0 = (1<<OCF0A) ;  // Pre-clearing any values from OCF0A bit
	
	/*-------------------------------------------------------- Calculation -----------------------------------------------------------
	F_CPU = 16000000 Hz
	prescalar = 64
	
	F_timer = 16000000/64 = 250000 Hz = 250KHz
	T_tick = 1 / 250000 = 0.000004 sec = 4 us
	
	Required delay = 1ms = 1000us
	Required ticks = (Required delay / T_tick) - 1 
	               = (1000 / 4) - 1
				   = 250 count - 1
				   = 249 ticks
				   
	Therefore Load OCROA = 249 for 1ms delay			   
	
	*/
	
	// Loading OCR0A with 249
	OCR0A = 249 ;  
	
	// Configure Prescalar as 64
	TCCR0B |= ((1<<CS01) | (1<<CS00)) ;
	TCCR0B &= ~(1<<CS02) ;
	
	// Enable Local Interrupt 
	TIMSK0 |= (1<<OCIE0A) ;
}

void gpio_init ()
{
	DDRB |= (1<<DDB5) ;  // Configure DDRB pin 5 High (Output mode)
	PORTB &= ~(1<<PORTB5) ;  // Initializing LED in OFF state
}

int main(void)
{
    gpio_init() ;
	timer0_CTCmode_interrupt_1sec() ;
	
	sei() ;   // Enable Global Interrupt
	
    while (1) 
    {
    }
}

