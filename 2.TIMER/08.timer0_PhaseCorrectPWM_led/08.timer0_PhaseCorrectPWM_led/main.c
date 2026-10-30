/*
 * 08.timer0_PhaseCorrectPWM_led.c
 *
 * Created: 23-10-2026 22:16:44
 * Author : HP
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

//phase correct PWM configuration function
void  timer0_phasecorrect_pwm_init()
{
	//step 1: configuring PD6 as Output (OCR0A)
	DDRD |= (1 << DDD6);
	//step 2: configuring timer0 in phase correct PWM mode
	TCCR0A |= (1 << WGM00);
	TCCR0A &= ~(1 << WGM01);
	/*----------------------calculation----------------------------
	
	F_pwm = F_CPU / (2 x N * 256), where N = Prescaler value
	F_CPU = 16,000,000 MHz
	N = 256
	
	F_pwm = 16000000 / (2 x 256 x 256)
		  = 16000000 / (131072)
		  = 122 Hz
	*/
	//step 4: configuring prescaler value as 256
	TCCR0B &= ~((1 << CS01) | (1<<CS00));
	TCCR0B |= (1 << CS02) ;
	//step 5: configuring in non-inverting mode
	TCCR0A |= (1 << COM0A1);
	
}

int main(void)
{
	//calling function
	timer0_phasecorrect_pwm_init();
	
    while (1) 
    {
		//loop 1: brightness Increment 
		for (uint8_t i=0 ; i < 255 ; ++i)
		{
			OCR0A = (uint8_t)i;
			_delay_ms(10);
		}		
		
		//loop 2: brightness Decrement
		for (uint8_t i=255 ; i > 0; --i)
		{
			OCR0A = (uint8_t)i;
			_delay_ms(10);
		}
    }
}
