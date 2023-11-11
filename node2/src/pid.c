#include <pid.h>
#include "uart_and_printf/printf-stdarg.h"

const float dt = 0.01;
const float kp_pos = 15;
const float kp_vel = 3;
const float ki_vel = 20;
float e_int = 0;
uint32_t prev_pos = 0;

void get_pos_vel(uint32_t* pos ,int32_t* vel)                               //Finds the current position and speed of the motor
{
    *pos = read_motor_encoder();                                            //Reads current speed from encoder.
    *vel = ((int)*pos - (int)prev_pos)/dt;                                  //Calculate current speed
    prev_pos = *pos;
}

int32_t pos_controller(uint32_t target_pos, uint32_t current_pos)           //Controls position by calculating target vel
{
    int32_t error = (target_pos - current_pos);                             // Calculate error
    int32_t target_vel = (int)(kp_pos*(float)error);                        // Calcualte target power
    return target_vel;
}

int32_t vel_controller(uint32_t target_vel, uint32_t current_vel)           //calculates output power based on target vel for pos contr.
{
    int32_t error = (target_vel - current_vel);                             // Calculate error
    e_int += ki_vel*(float)error*dt;                                        // Calculate I-ledd
    const int maxint = 3000;                                       
    if (e_int > maxint) e_int = maxint;                                     // Limit integral
    if (e_int < - maxint) e_int= -maxint;
    int32_t u_vel = (int)(kp_vel*(float)error + e_int);                     // Calcualte power
    const int maxpower = 3000;
    if (u_vel > maxpower) u_vel = maxpower;                                 // Limit output
    if (u_vel < -maxpower) u_vel= -maxpower;        
    return u_vel;
}




