//uart header

// SOURCE: DATASHEET

// INCLUDES
#include <avr/io.h>
#include <utility/delay.h>
#include <stdlib.h>


// DEFINES
#define BAUD 9600 // baud rate
#define FOSC 4913200 // some clock stuff? is it F_CPU?
#define MYUBRR FOSC/16/BAUD-1 // uart baud rate register

// FUNCTIONS
void uart_init();

void uart_transmit(char data);

void uart_receive();
