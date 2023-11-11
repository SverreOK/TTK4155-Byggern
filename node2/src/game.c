#include "game.h"
#include "motor_controller.h"
#include "pid.h"
#include "score.h"
#include "uart_and_printf/printf-stdarg.h"

// VARIABLES
uint8_t score;
uint32_t motor_target = 700;
uint32_t score_delay = SCORE_DELAY;

void start_game() {
    score = 0;
    printf("GAME STARTING!\n");
    printf("Losses: %d\n", score);
}

void tick_game() {
    if (calibrating) {
        encoder_calibration();
        calibrating = 0;
    }
    else{

        uint32_t pos;
        int32_t vel;
        get_pos_vel(&pos, &vel);                                
        int32_t target_vel = pos_controller(motor_target, pos);     // Calculates target velocity
        int32_t power = vel_controller(target_vel, vel);            // Calculates output power
        motor_controller_set_power(power);                          
    }

    // Manage score
    score_update();
    if (score_new_goal())
    {
        score++;
        printf("Losses: %d\n", score);
    }
}