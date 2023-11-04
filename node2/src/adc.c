#include "adc.h"
#include "sam.h"

// void adc_init() {
//     ADC->ADC_MR |= ADC_MR_PRESCAL(2); // Max clock frequency
//     ADC->ADC_MR |= ADC_MR_TRACKTIM(8); //Cycles for trackiing and stabilizing voltage
//     ADC->ADC_MR |= ADC_MR_TRANSFER()



//     // Configure the ADC clock
//     PMC->PMC_PCER1 = (1 << 5);  // Enable ADC peripheral clock
//     ADC->ADC_MR = ADC_MR_PRESCAL(3) | ADC_MR_STARTUP_SUT64 | ADC_MR_SETTLING_AST3;
//     ADC_CR
    
//     // Enable ADC channel
//     ADC->ADC_CHER = ADC_CHER_CH0; // Enable channel 0

//     // Start conversions
//     ADC->ADC_CR = ADC_CR_START;
// }

void adc_init() {
    REG_ADC_MR |= ADC_MR_FREERUN;

    REG_ADC_CHER |= ADC_CHER_CH0;

    REG_ADC_CR = ADC_CR_START;
}

uint16_t adc_read() {
    return ADC->ADC_CDR[0]; // Read the converted value from channel 0
}

// // working
// void adc_init(){  //kok
// 	PMC->PMC_PCR |= (37<<0);
// 	PMC->PMC_PCER1 |= 1 <<(37-32);
// 	ADC->ADC_CR = ADC_CR_START;
// 	ADC->ADC_MR = ADC_MR_FREERUN;
// 	ADC->ADC_CHER = ADC_CHDR_CH0;
// }

// uint16_t adc_read(){
// 	return ADC->ADC_CDR[0];
// }