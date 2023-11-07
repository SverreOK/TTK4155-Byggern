#ifndef GAME_H_
#define GAME_H_

#include <stdint.h>

// DEFINES
#define SCORE_DELAY 2000

// VARIABLES
uint32_t motor_target;


// FUNCTIONS
void start_game();

/* !TICK_GAME!
Does everything that needs to be done in a loop.
- PID Controller Update and motor steering
- Check score --> Check IR sensor
- Check button and servo from joystick
*/
void tick_game();

uint8_t check_goal();

#endif