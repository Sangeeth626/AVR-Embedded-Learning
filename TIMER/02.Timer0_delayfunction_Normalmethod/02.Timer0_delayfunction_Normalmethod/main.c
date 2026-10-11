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

#define F_CPU 16000000
#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

