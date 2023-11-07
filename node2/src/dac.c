#include "dac.h"
#include "sam.h"

void dac_init() {
    // See 9.1 in ATSAM3XE for process identifier. Here you see PID37 refers to ADC controller
    // Enabling the ADC peripheral clock by setting the bit in specified peripheral position
    REG_PMC_PCER1 |= PMC_PCER1_PID38;

    // Select channel 1 as specified in lab tutorial
    REG_DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;

    // Enable channel 1
    REG_DACC_CHER |= DACC_CHER_CH1;

}

// Setting the value for the DAC 4095 is the highest value giving 5 V
void dac_output(uint16_t value) {
    REG_DACC_CDR = value;
}