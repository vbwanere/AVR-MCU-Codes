/*
 * Serialprint.c
 *
 * Created: 10/10/2023 3:07:16 PM
 * Author : 
 */ 

#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((16000000UL / (9600UL * 16UL))) - 1)

/*--------------------Libraries---------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "uart.h"

/*--------------------Variables---------------------------*/
char String[25];

/*-----------------------------------------------------------*/

int main(void) {
	UART_init(BAUD_PRESCALER);
	DDRB |= (1 << 5); // Set PORTB pin 5 as output. (pin 13 on Arduino UNO)
	while(1) {
		UART_putstring("Hello User!\r\n");
		_delay_ms(100);
		UART_putstring("LED ON for 1 sec\r\n");
		PORTB |= (1 << 5); // Turn on the LED
		_delay_ms(1000);
		UART_putstring("LED OFF for 1 sec\r\n");
		PORTB &= ~(1 << 5); // Turn off the LED
		_delay_ms(1000);
	}
}

