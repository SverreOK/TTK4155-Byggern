#ifndef DAC_H_
#define DAC_H_

#include <stdint.h>

void dac_init();

void dac_output(uint16_t value);

#endif