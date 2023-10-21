#include "../inc/adc.h"
#include <avr/io.h>

#define ADC_ADDRESS 0x1400

void adc_init() {
    // Fra henrikhestnes Byggern adc.c

    // set PB0 to output PWM timer signal
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

    // TCCR0 = (1 << WGM01) | (1 << CS01) | (1 << CS00);
    // OCR0 = 125;
    // DDRD |= (1 << DDD5);
    // TCCR0 |= (1 << COM01) | (1 << COM00);
    // TCCR0 |= (1 << CS00);

    // DDRD |= (1<<PD5);
    // TCCR1A |= (1<<WGM20)|(WGM21);
    // TCCR1A |= (1<<COM20)|(1<<CS20)|(0<<CS21)|(0<<CS22);

    // OCR2 = 128;
}

uint8_t adc_read(uint8_t channel)
{
    volatile char *adc_data = (char *) ADC_ADDRESS;

    adc_data[0] = 0;

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

    for (int i = 0; i <= 4; i++)
    {
        adc_measurements[i] = adc_data[0];
    }
}