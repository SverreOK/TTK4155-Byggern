#include "timer_interrupt.h"
#include "sam.h"

const int interrupt_freq = 100;
void (*callback)();

void timer_interrupt_init(void (*timer_callback)())
{
    callback = timer_callback;
    
    PMC->PMC_PCER0 |= (1 << ID_TC0);                                    // Enable the peripheral clock for TC0
    TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC;      // Waveform mode
    TC0->TC_CHANNEL[0].TC_RC = SystemCoreClock / (2*interrupt_freq);    // Set frequency
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;            // Start timer
    NVIC_EnableIRQ(TC0_IRQn);                                           // Enable the TC0 channel 0 interrupt in the NVIC
    TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;                            // Enable the RC compare interrupt
    TC0->TC_CHANNEL[0].TC_SR;                                           // Enable the interrupt in status register
}

void TC0_Handler(void)
{
    callback();

    TC0->TC_CHANNEL[0].TC_SR; // Clear interrupt flag
}