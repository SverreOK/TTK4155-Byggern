#include <pid.h>
#include "uart_and_printf/printf-stdarg.h"

const float dt = 0.01;
const float kp = 5;
const float ki = 0;
const float kd = 500;
int32_t prev_error = 0;
float e_int = 0;

int32_t pid_controller(uint32_t target, uint32_t encoder){

    int32_t error = (target - encoder);                                // Calculate error
    e_int += ki*(float)error*dt;
    float e_delta = (float)(error - prev_error)*dt;
    int32_t u = (int)(kp*(float)error + e_int + kd*e_delta);           // Calcualte control signal
    if (u > 3000) u = 3000;
    if (u < -3000) u = -3000;
                                                 // Calculate error integration
    prev_error = error;                                                // For D ledd
    // printf("P: %6d, I: %6d, D: %6d\n", (int)(kp*(float)error), (int)(e_int), (int)(kd*e_delta));
    
    return u;
}

