#include "solenoid.h"
#include "sam.h"

void solenoid_init() {
    //Enable GPIO on A0
    REG_PIOA_PER |= PIO_PA16;
    // Enable output
    REG_PIOA_OER |= PIO_PA16;
    // Set data to be driven to A0 
    REG_PIOA_SODR |= PIO_PA16;
}

void solenoid_on() {
    // Clear data to be driven to A0
    REG_PIOA_CODR |= PIO_PA16;
}

void solenoid_off() {
    // Set data to be driven to A0
    REG_PIOA_SODR |= PIO_PA16;
}
