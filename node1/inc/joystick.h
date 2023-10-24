#include <stdint.h>

void joystick_calibrate();

typedef enum {NEUTRAL, UP, DOWN, LEFT, RIGHT, PRESS} joystick_action;

uint8_t joystick_x();
uint8_t joystick_y();

void joystick_poll_action(); // Should be called often

joystick_action joystick_get_action(); // Gives the most recent action. Clears action when read.

void joystick_test();