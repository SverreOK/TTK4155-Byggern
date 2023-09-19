#include "../inc/xmem.h"
#include <avr/io.h>

void xmem_init() {
    MCUCR |= (1<<SRE); // xmem enable

    SFIOR |= (1<<XMM2);
    SFIOR &= ~(1<<XMM1);
    SFIOR &= ~(1<<XMM0);
    //SFIOR |= (1<<XMBK);
}