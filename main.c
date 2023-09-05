//test
#define F_CPU 4915200
#define BLINK_HZ 20

#include <avr/io.h>
#include <util/delay.h>
#include "inc/uart.h"

void blinkLED();
void testUART();

int main(void) {
    testUART();
    return 0;
}

void testUART() {
    uart_init(MYUBRR);
    while(1) {
        uart_transmit('a');
        blinkLED();
    }
}

void blinkLED() {
    DDRA |= (1 << PA0);

    PORTA |= (1 << PA0);
    _delay_ms(1000/BLINK_HZ/2);
    PORTA &= ~(1 << PA0);
    _delay_ms(1000/BLINK_HZ/2);
    // while (1) {
    // }
}