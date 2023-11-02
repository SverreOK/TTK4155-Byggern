#include "../inc/adc.h"
#include <avr/io.h>
#include <util/delay.h>

#define ADC_ADDRESS 0x1400

#define F_CPU 4.9152E6

void adc_init() {
    
    
    // FUNGERENDE! 

    // Fra henrikhestnes Byggern adc.c
    DDRB |= 1;
    // set to CTC mode
    TCCR0 |= (1 << WGM01);
    TCCR0 &= ~(1 << WGM00);
    
    // set PWM toggle on match with internal clock
    TCCR0 &= ~(1 << COM01);
    TCCR0 |= (1 << COM00);

    // set PWM signal to match with internal clock, no prescale
    TCCR0 &= ~(1 << CS02);
    TCCR0 &= ~(1 << CS01);
    TCCR0 |= (1 << CS00);

    // frequency set to 0.5 x F_CPU
    OCR0 = 0;
}

uint8_t adc_read(uint8_t channel)
{
    volatile char *adc_data = (char *) ADC_ADDRESS;

    adc_data[0] = 0;
    _delay_ms(1);

    uint8_t val;

    for (int i = 0; i <= channel; i++)
    {
        val = adc_data[0];
    }

    return val;
}

void adc_read_all(volatile uint8_t *adc_measurements)
{
    volatile char *adc_data = (char *) ADC_ADDRESS;

    adc_data[0] = 0;
    _delay_ms(1);

    for (int i = 0; i <= 4; i++)
    {
        adc_measurements[i] = adc_data[0];
    }
}