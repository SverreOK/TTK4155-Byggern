

void joystick_calibrate();

typedef enum {NEUTRAL, UP, DOWN, LEFT, RIGHT, PRESS} joystick_action;

void joystick_poll(); // Should be called often

joystick_action joystick_get_action(); // Gives the most recent action. Clears action when read.

void joystick_test();