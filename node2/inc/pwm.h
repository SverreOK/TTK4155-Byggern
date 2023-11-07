#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>

void pwm_init();

void pwm_set_dutycycle(float dutycycle);

void pwm_set_dutycycle_ms(int ms);

void pwm_set_position(uint8_t pos);

#endif /*PWM_H_*/