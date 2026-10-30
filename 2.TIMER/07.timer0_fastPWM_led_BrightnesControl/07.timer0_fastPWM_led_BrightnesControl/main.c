/*
 * 07.timer0_fastPWM_led_BrightnesControl.c
 *
 * Created: 23-10-2026 22:15:25
 * Author : HP
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void timer0_fast_pwm_init()
{
	DDRD |= (1<<DDD6) ;   // Configuring PD6 as Output because OCR0A lies in PD6
	
	// Configuring in fast PWM mode
	TCCR0A |= ((1<<WGM01) | (1<<WGM00)) ;
	TCCR0B &= ~(1<<WGM02) ; 
	
	/* ------------------------------- Calculation ---------------------------------------------
	F_pwm = F_CPU / (N * 256)  , where N is prescalar value
	
	Led need 1KHz frequency , So we need to choose suitable Prescalar value in order to get 1KHz
	Let Prescalar = 64 
	
	F_pwm = 16,000,000 / (64 * 256)
	      = 976.5 Hz  ~= 1Khz 
		  
		  Therefore prescalar is taken as 64  
     */
	
	// Configuring prescalar as 64
	TCCR0B |= ((1<<CS01) | (1<<CS00)) ;
	TCCR0B &= ~(1<<CS02);
	
	// Configuring in non-inverting mode
	TCCR0A |= (1<<COM0A1) ;
	TCCR0A &= ~(1<<COM0A0) ;
}

int main(void)
{
	uint8_t i ;
	
    timer0_fast_pwm_init() ;
	
	while(1)
	{
		// Brightness Increment
		for(i=0 ; i<255 ; i++)
		{
			OCR0A = i ;
			_delay_ms(10);
		}
		
		// Brightness Decrement
		for(i=255 ; i>0 ; i--)
		{
			OCR0A = i;
			_delay_ms(10) ;
		}
	}
}








