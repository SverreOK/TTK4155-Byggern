#ifndef MOTOR_CONTROLLER_H_
#define MOTOR_CONTROLLER_H_

#include <stdint.h>

void motor_controller_init();

void motor_encoder_init();

void motor_controller_set_position();

void motor_controller_set_speed(int32_t value);

void motor_controller_set_direction(uint8_t dir);

uint16_t read_motor_encoder();

void motor_run_joystick();

void encoder_reset();

void encoder_calibration();


#endif