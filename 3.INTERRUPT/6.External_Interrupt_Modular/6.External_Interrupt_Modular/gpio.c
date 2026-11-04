/*
 * gpio.c
 *
 * Created: 04-11-2026 22:15:35
 *  Author: HP
 */ 

#include "gpio.h"

void gpio_init()
{
	//configuring PB5 as Output
	DDRB |= (1 << DDB5);
}
