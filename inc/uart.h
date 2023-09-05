// SOURCE: DATASHEET

// INCLUDES
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

// DEFINES
#define BAUD 9600 // baud rate
#define FOSC 4915200 // some clock stuff? is it F_CPU?
#define MYUBRR FOSC/16/BAUD-1 // uart baud rate register

// FUNCTIONS
void uart_init(unsigned int ubrr);

void uart_transmit(unsigned char data);

unsigned char uart_receive();

void uart_flush();