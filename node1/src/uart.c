//uart source

// Inspiration taken from ATmega162 datasheet

#include "../inc/uart.h"
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>

void uart_transmit(unsigned char data, FILE* f) {

    while (! (UCSR0A & (1<<UDRE0)));

    UDR0 = data;
}

unsigned char uart_receive(FILE* f) {
    while (!(UCSR0A & (1 << RXC0)));

    return UDR0;
}

FILE* uart_init(unsigned int ubrr) {

    // Set BAUD rate
    UBRR0H = (unsigned char) (ubrr>>8);
    UBRR0L = (unsigned char) ubrr;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    UCSR0C = (1<<URSEL0) | (1<<USBS0) | (3<<UCSZ00);

    return fdevopen(&uart_transmit, &uart_receive);
}