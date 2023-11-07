#include "adc.h"
#include "sam.h"

void adc_init() {

    // See 9.1 in ATSAM3XE for process identifier. Here you see PID37 refers to ADC controller
    // Enabling the ADC peripheral clock by setting the bit in specified peripheral position
    REG_PMC_PCER1 |= PMC_PCER1_PID37;

    // Enabling freerun (continuous sampling) as recommended in ovingforelesning
    REG_ADC_MR |= ADC_MR_FREERUN;

    // Enabling sampling on channel 0
    REG_ADC_CHER |= ADC_CHER_CH0;

    // Starting sampling on channel 0
    REG_ADC_CR = ADC_CR_START;
}

 // Read the latest converted value from channel 0
uint16_t adc_read() {
    return ADC->ADC_CDR[0];
}

// Checks if value if belows thresshold and returns 1 if it is
uint8_t adc_value_below_threshold(int threshold) {
    if (adc_read() >= threshold) {
        return 0;
    }
    else {
        return 1;
    }
}

// working stuff to add
// 	PMC->PMC_PCR |= (37<<0);
// 	PMC->PMC_PCER1 |= 1 <<(37-32);