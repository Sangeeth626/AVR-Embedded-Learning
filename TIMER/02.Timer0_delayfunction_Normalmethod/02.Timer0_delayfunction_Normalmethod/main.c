/*
 * 02.Timer0_delayfunction_Normalmethod.c
 *
 * Created: 11-10-2026 20:12:45
 * Author : Sangeeth
 */ 
/* Que) Write an Embedded C program for the ATmega328P microcontroller running at a clock frequency of 16 MHz to generate a delay of approximately 1 second using Timer0 in Normal Mode, using Method 1 (overflow counting).
        Implement the program twice: first using a prescaler of 64 and then using a prescaler of 256.
        For each configuration, calculate the timer clock frequency, the overflow time, the number of overflows required, and the initial value to be loaded into the TCNT0 register, if necessary, to achieve the required delay. Use polling of the TOV0 overflow flag in the TIFR0 register to detect timer overflows, and toggle an LED connected to PB5 after every 1-second delay.
		Do not use software delay functions such as _delay_ms() or timer interrupts. */

/* Step 1 : Create a function which configure timer0 for normal mode and select proper clock
   Step 2 : Perform calculation for finding number of overflow in 1second
   Step 3 : Create a delay function
   Step 4 : Write main function 
*/   

#define F_CPU 16000000
#include <avr/io.h>

void timer0_config_8()
{
	TCCR0A &= ~((1<<WGM01) | (1<<WGM00)) ;            // Configure in normal mode
	TCCR0B &= ~((1<<CS02) | (1<<CS01) | (1<<CS00));   // Clearing register before setting
	TCCR0B |= (1<<CS01) ;                             // Configure for clock prescalar 8
}

void timer0_config_64()
{
	TCCR0A &= ~((1<<WGM01) | (1<<WGM00)) ;            // Configure in normal mode
	TCCR0B &= ~((1<<CS02) | (1<<CS01) | (1<<CS00));   // Clearing register before setting
	TCCR0B |= ((1<<CS01) | (1<<CS00)) ;               // Configure for clock prescalar 64
}

void timer0_config_256()
{
	TCCR0A &= ~((1<<WGM01) | (1<<WGM00)) ;             // Configure in normal mode
	TCCR0B &= ~((1<<CS02) | (1<<CS01) | (1<<CS00));    // Clearing register before setting
	TCCR0B |= (1<<CS02) ;                              // Configure for clock prescalar 256
}

void delay_1sec_pre8()
{
	for(uint16_t i=1 ; i <=7812 ; ++i)        // 7812 is the number of overflow in one second for prescalar clock 8 , We need uint_16t (0-65535)
	{
		while(!(TIFR0 & (1<<TOV0)))
		{
			// Waiting for overflow
		}
		
		TIFR0 |= (1<<TOV0) ;
	}
}

void delay_1sec_pre64()
{
	for(uint16_t i=1 ; i<=977 ; ++i)        // 977 is the number of overflow in one second for prescalar clock 64 , We need uint_16t (0-65535)
	{
		while(!(TIFR0 & (1<<TOV0)))
		{
			// Waiting for overflow
		}
		
		TIFR0 |= (1<<TOV0) ;
	}
}

void delay_1sec_pre256()
{
	for(uint8_t i=1 ; i<=244 ; ++i)        // 244 is the number of overflow in one second for prescalar clock 256 , We only need uint_8t (0-255)
	{
		while(!(TIFR0 & (1<<TOV0)))
		{
			// Waiting for overflow
		}
		
		TIFR0 |= (1<<TOV0) ;
	}
}

void LEDtoggle_B5()
{	
	PORTB ^= (1<<PORTB5) ;    // LED ON
	delay_1sec_pre8() ;       // wait 1 second
	PORTB ^= (1<<PORTB5) ;    // LED OFF
}

void LEDtoggle_B4()
{
	PORTB ^= (1<<DDB4) ;
	delay_1sec_pre64() ;
	PORTB ^= (1<<DDB4) ;
}

void LEDtoggle_B3()
{
	PORTB ^= (1<<DDB3);
	delay_1sec_pre256();
	PORTB ^= (1<<DDB3);
}

int main(void)
{
	DDRB |= ((1<<DDB5) | (1<<DDB4) | (1<<DDB3)) ;
	
	while(1)
	{
		timer0_config_8() ;
		LEDtoggle_B5() ;
		
		timer0_config_64() ;
		LEDtoggle_B4() ;
		
		timer0_config_256() ;
		LEDtoggle_B3() ;
	}
}

