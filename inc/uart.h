//uart header

// SOURCE: DATASHEET

#include <avr/io.h>
#include <utility/delay.h>
#include <stdlib.h>

#define BAUD 9600
#define FOSC 4913200
#define MYUBRR FOSC/16/BAUD-1

void uart_transmit(char data);

void uart_receive();
