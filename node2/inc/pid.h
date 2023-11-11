#ifndef PID_H_
#define PID_H_

#include <stdint.h>

//FUNCTIONS
int32_t pid_controller(uint32_t target, uint32_t encoder);
void get_pos_vel(uint32_t* pos ,int32_t* vel);
int32_t pos_controller(uint32_t target_pos, uint32_t current_pos);
int32_t vel_controller(uint32_t target_vel, uint32_t current_vel);
#endif