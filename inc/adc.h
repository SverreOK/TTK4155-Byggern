#include <stdint.h>

void adc_init();
uint8_t adc_read(uint8_t channel);
void adc_read_all(volatile uint8_t *adc_measurements);