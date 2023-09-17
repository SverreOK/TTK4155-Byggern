#include "../inc/io.h"
#include <avr/io.h>

void io_input_init()
{
    DDRB &= ~(1 << DDB1) & ~(1 << DDB2) & ~(1 << DDB2);  // Port B pins 1, 2, 3 as inputs
    PORTB |= (1 << PORTB1);
    PORTB &= ~(1 << PORTB2) & ~(1 << PORTB3);
}

bool io_read(uint8_t pin_nr)
{
    return PINB & (1 << (PINB0 + pin_nr));
}