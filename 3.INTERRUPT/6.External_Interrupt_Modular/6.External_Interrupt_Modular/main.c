/*
 * 6.External_Interrupt_Modular.c
 *
 * Created: 04-11-2026 22:05:05
 * Author : HP
 */ 

#define F_CPU 16000000UL
#include "External_interrupt.h"
#include "gpio.h"


int main(void)
{
    gpio_init() ;
	external_interrupt_INT0_init() ;
	
    while (1) 
    {
    }
}

