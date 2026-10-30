/*
 * 01_gpio_output.c
 *
 * Created: 05-10-2026 21:34:43
 * Author : HP
 */ 

#define F_CPU 16000000UL	//Include the clock frequency
#include <avr/io.h>
#include <util/delay.h> //for delay functions


int main(void)
{
	//setting the pin direction
	DDRB |= (1 << DDB5); //Configured PORTB PIN 5 as Output - using bitwise
	DDRB |= (1 << DDB4); //Configured PORTB PIN 4 as Output - using bitwise
	DDRB |= (1 << DDB3); //Configured PORTB PIN 3 as Output - using bitwise
	while (1)
	{
		PORTB |= (1 << PORTB5); //Making PORTB PIN 5 High.
		_delay_ms(500);
		PORTB |= (1 << PORTB4); //Making PORTB PIN 4 High.
		_delay_ms(500);
		PORTB |= (1 << PORTB3); //Making PORTB PIN 3 High.
		_delay_ms(500); //since 1000 ms = 1 second
		PORTB &= ~(1 << PORTB5); //Making PORTB PIN 5 Low.
		_delay_ms(500);
		PORTB &= ~(1 << PORTB4); //Making PORTB PIN 4 Low.
		_delay_ms(500);
		PORTB &= ~(1 << PORTB3); //Making PORTB PIN 3 Low.
		_delay_ms(500);
	}
}

