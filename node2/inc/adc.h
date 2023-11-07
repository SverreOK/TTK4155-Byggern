#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void adc_init();

uint16_t adc_read();

uint8_t adc_value_below_threshold(int threshold);

#endif /*ADC_H_*/