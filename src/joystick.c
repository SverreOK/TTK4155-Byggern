#include "joystick.h"
#include <stdint.h>
#include "adc.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>

const uint8_t joystick_threshold = 100;

uint8_t x_mid = 128;
uint8_t y_mid = 128;

joystick_action action = NEUTRAL;

// uint8_t action_status = 0b00000000; // Each bit indicates wether an action is active or not
uint8_t up_active = 0;
uint8_t down_active = 0;
uint8_t left_active = 0;
uint8_t right_active = 0;
uint8_t button_active = 0;

void joystick_calibrate()
{
    x_mid = adc_read(JOY_X);
    y_mid = adc_read(JOY_Y);
}

uint8_t joystick_x()
{
    uint8_t value = adc_read(JOY_X);
    if (value < x_mid)  return value*128/x_mid;
    else                return 255 - (255-value)*128/(255-x_mid);
}

uint8_t joystick_y()
{
    uint8_t value = adc_read(JOY_Y);
    if (value < y_mid)  return value*128/y_mid;
    else                return 255 - (255-value)*128/(255-y_mid);
}

void joystick_poll()
{
    int8_t x = joystick_x() - 128;
    int8_t y = joystick_y() - 128;
    uint8_t button = (!io_read(1));
    
    if (x > joystick_threshold)
    {
        if (!right_active)  {right_active = 1;  action = RIGHT;}
    }
    else right_active = 0;

    if (-x > joystick_threshold)
    {
        if (!left_active)   {left_active = 1;   action = LEFT;}
    }
    else left_active = 0;

    if (y > joystick_threshold)
    {
        if (!up_active)     {up_active = 1;     action = UP;}
    }
    else up_active = 0;

    if (-y > joystick_threshold)
    {
        if (!down_active)   {down_active = 1;   action = DOWN;}
    }
    else down_active = 0;

    if (button)
    {
        if (!button_active) {button_active = 1; action = PRESS;}
    }
    else button_active = 0;
}

joystick_action joystick_get_action()
{
    joystick_action a = action;
    action = NEUTRAL;
    return a;
}

void joystick_test()
{
    joystick_poll();

    printf("Action: %d\n", joystick_get_action());
}