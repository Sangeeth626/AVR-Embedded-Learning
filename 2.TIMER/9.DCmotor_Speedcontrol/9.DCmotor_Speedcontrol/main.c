/*
 * 9.DCmotor_Speedcontrol.c
 *
 * Created: 03-11-2026 19:39:37
 * Author : HP
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void timer0_fastPWM_init()
{
	// 1. Configure PD6 in output mode because OCR0A lies in PD6
	DDRD |= (1<<DDD6);
	
	// 2. Configure timer0 in Fast PWM mode
	TCCR0A |= ((1<<WGM01) | (1<<WGM00));
	TCCR0B &= ~(1<<WGM02) ;
	
	/*---------------------------------------------------------- Calculation --------------------------------------------------------------
	For DC motor speed control frequency range between 5KHz to 20KHz is recommended
	we have F_CPU = 16000000
	Assume Prescalar = 8
	
	Fpwm = 16000000/(8*256) = 7812.5 ~= 7.8 KHz (This is the recommended frequency, therefore we choose Prescalar as 8)
	
	*/
	
	// 3. Configure prescalar as 8
	TCCR0B |= (1<<CS01) ;
	TCCR0B &= ~((1<<CS02) | (1<<CS00)) ;
	
	// 4. Configure in non-inverting mode
	TCCR0A |= (1<<COM0A1) ;
	TCCR0A &= ~(1<<COM0A0) ;
}

void dc_motor_init()
{
	DDRD |= ((1<<DDD1) | (1<<DDD2)) ;   // Setting DDRD Pin 1 and 2 in Output mode
}

static void ramp_up()
{
	uint8_t i ;
	
	for(i=0 ; i<255 ; i++)
	{
		OCR0A = i ;
		_delay_ms(10);
	}
}

static void ramp_down()
{
	uint8_t i ;
	
	for(i=255 ; i>0 ; i--)
	{
		OCR0A = i ;
		_delay_ms(10);
	}
}

void forward_rotation()    // for Forward rotation (D1-ON and D2-OFF)
{
	PORTD |= (1<<PORTD1);
	PORTD &= ~(1<<PORTD2);
}

void reverse_rotation()   // for Reverse rotation (D1-OFF and D2-ON)
{
	PORTD &= ~(1<<PORTD1);
	PORTD |= (1<<PORTD2) ;
}

void stop_rotation()
{
	PORTD &= ~((1<<PORTD1) | (1<<PORTD2));
	_delay_ms(500);
}

int main(void)
{	
    timer0_fastPWM_init() ;
	dc_motor_init() ;
	
    while (1) 
    {
		forward_rotation() ;
		ramp_up();
		ramp_down();

		stop_rotation();
		
		reverse_rotation();
		ramp_up();
		ramp_down();

		stop_rotation();
    }
}
