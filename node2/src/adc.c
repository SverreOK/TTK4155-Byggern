#include "adc.h"

void adc_init() {
    // Configure the ADC clock
    PMC->PMC_PCER1 = (1 << 5);  // Enable ADC peripheral clock
    ADC->ADC_MR = ADC_MR_PRESCAL(3) | ADC_MR_STARTUP_SUT64 | ADC_MR_SETTLING_AST3;
    
    // Enable ADC channel
    ADC->ADC_CHER = ADC_CHER_CH0; // Enable channel 0

    // Start conversions
    ADC->ADC_CR = ADC_CR_START;
}

uint32_t adc_read() {
    while (!(ADC->ADC_ISR & ADC_ISR_DRDY)) {
        // Wait for conversion to complete
    }
    return ADC->ADC_CDR[0]; // Read the converted value from channel 0
}