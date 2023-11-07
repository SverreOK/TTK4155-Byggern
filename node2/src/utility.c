#include "utility.h"
#include "sam.h"

void delay_ms(uint32_t milliseconds) {
    volatile uint32_t i;
    uint32_t cycles = milliseconds * (SystemCoreClock / 1000 / 14);

    for (i = 0; i < cycles; i++) {
        __NOP(); // This is a no-operation instruction
    }
}

void delay_us(uint32_t microseconds) {
    volatile uint32_t i;
    uint32_t cycles = microseconds * (SystemCoreClock / 1000000 / 14);

    for (i = 0; i < cycles; i++) {
        __NOP(); // This is a no-operation instruction
    }
}