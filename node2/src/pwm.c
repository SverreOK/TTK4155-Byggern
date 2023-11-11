#include "pwm.h"
#include "sam.h"

void pwm_init() {
    REG_PWM_CLK = PWM_CLK_DIVA(42) | PWM_CLK_PREA(0); 

    REG_PMC_PCER1 |= PMC_PCER1_PID36;

     // Disable PIO
    REG_PIOC_PDR |= PIO_PDR_P19;
    // AB peripheral select --> Choose pin 44 and 45
    REG_PIOC_ABSR |= PIO_ABSR_P19;

    REG_PWM_WPCR = PWM_WPCR_WPKEY(0x50574D); //write enable
    REG_PWM_WPCR |= PWM_WPCR_WPRG0 | PWM_WPCR_WPRG2 | PWM_WPCR_WPRG3 | PWM_WPCR_WPCMD(0);

    REG_PWM_CMR5 = PWM_CMR_CALG | PWM_CMR_CPRE_CLKA;
    // Initial setting of dutycycle
    // CHECK VALUES
    REG_PWM_CPRD5 |= 20000; // Set frequency
    // Enabling PWM and waiting for it to be asserted
    REG_PWM_ENA = PWM_ENA_CHID5;
    REG_PWM_CDTY5 |= 18500; // Set dutycycle

    printf("PWM ENABLED CHANNEL 5 / PIN 44\n");		
}

void pwm_set_dutycycle(float dutycycle) {
    if (dutycycle > 1 || dutycycle < 0) {
        printf("Dutycycle needs to be between 0 and 1\n");
        return;
    }

    uint32_t max_duty = REG_PWM_CPRD5; // max duty cycle, this should be set by us from the start (?)

    uint32_t new_duty = (uint32_t)max_duty * (float)(1. - dutycycle); // simple enough

    REG_PWM_CDTY5 = new_duty;// new_duty; // assigning new dutycycle
}

void pwm_set_dutycycle_ms(int ms) {
    if (ms < 1000 || ms > 2000) {
        printf("PWM must be between 1000 and 2000 ms\n");
    }

    REG_PWM_CDTY5 = REG_PWM_CPRD5 - ms;
}

void pwm_set_position(uint8_t pos) {
    if (pos > 255 || pos < 0) {
        printf("Position must be between 0 and 90 degrees");
    }
    
    int ms = (int) 1000 + (pos*1000)/255;

    REG_PWM_CDTY5 = REG_PWM_CPRD5 - ms;
}