/*
 * 3.Timer0_CTCmode_Interrupt_LEDtoggle_2sec.c
 *
 * Created: 30-10-2026 18:32:46
 * Author : HP
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile uint16_t match_count = 0 ;

ISR(TIMER0_COMPA_vect)
{ 
	match_count++ ;               // after 2ms TCNT0 reaches 124 and matches OCR0A, the hardware sets OCF0A and fires the interrupt, and TCNT0 resets to 0 on the next timer tick
	if(match_count >= 1000)       // After 1000 compare-matches (ie.. 1000 interrupt trigger count , LED toggle)
	{                                // 1000 compare-match * 2 ms(Time taken for TCNT0 reaches 124 and matches OCR0A) = 2 sec delay
		PORTB ^= (1<<PORTB5) ;
		match_count = 0 ;     // Resetting Overflow count for tracking next cycle
	}
}


void timer0_CTCmode_interrupt_2ms()
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
	
	Required delay = 2ms = 2000us
	Required ticks = (Required delay / T_tick) - 1 
	               = (2000 / 4) - 1
				   = 500 count - 1
				   = 499 ticks
	But timer0 is 8 bit register , the maximum value it can load is 255
	So we increase Prescalar to 256	
	
	
	F_timer = 16000000/256 = 62500 Hz = 62.5 KHz
	T_tick = 1 / 62500 = 0.000016 sec = 16 us
	
	Required delay = 2ms = 2000us
	Required ticks = (Required delay / T_tick) - 1
	= (2000 / 16) - 1
	= 125 count - 1
	= 124 ticks		   
				   
	Therefore Load OCROA = 124 for 2ms delay			   
	
	*/
	
	// Loading OCR0A with 124
	OCR0A = 124 ;  
	
	// Configure Prescalar as 256
	TCCR0B &= ~((1<<CS01) | (1<<CS00)) ;
	TCCR0B |= (1<<CS02) ;
	
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
	timer0_CTCmode_interrupt_2ms() ;
	
	sei() ;   // Enable Global Interrupt
	
    while (1) 
    {
    }
}