#include <stdint.h>

typedef enum {JOY_Y = 0, JOY_X, SLIDER_LEFT, SLIDER_RIGTH};

void adc_init();
uint8_t adc_read(uint8_t channel);
void adc_read_all(volatile uint8_t *adc_measurements);