#include "joystick.h"
#include <stdint.h>
#include "adc.h"
#include "io.h"
#include <stdio.h>

const uint8_t joystick_activate_threshold = 100;
const uint8_t joystick_deactivate_threshold = 80;

uint8_t x_mid = 128;
uint8_t y_mid = 128;

joystick_action action = NEUTRAL;

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

void joystick_poll_action()
{
    int8_t x = joystick_x() - 128;
    int8_t y = joystick_y() - 128;
    uint8_t button = (!io_read(1));
    
    if (x > joystick_activate_threshold)
    {
        if (!right_active)  {right_active = 1;  action = RIGHT;}
    }
    else if (x < joystick_deactivate_threshold) right_active = 0;

    if (-x > joystick_activate_threshold)
    {
        if (!left_active)   {left_active = 1;   action = LEFT;}
    }
    else if (-x < joystick_deactivate_threshold) left_active = 0;

    if (y > joystick_activate_threshold)
    {
        if (!up_active)     {up_active = 1;     action = UP;}
    }
    else if (y < joystick_deactivate_threshold) up_active = 0;

    if (-y > joystick_activate_threshold)
    {
        if (!down_active)   {down_active = 1;   action = DOWN;}
    }
    else if (-y < joystick_deactivate_threshold) down_active = 0;

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
    joystick_poll_action();

    printf("Action: %d\n", joystick_get_action());
}