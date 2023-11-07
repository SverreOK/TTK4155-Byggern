#include "game.h"
#include "motor_controller.h"
#include "pid.h"
#include "adc.h"
#include "uart_and_printf/printf-stdarg.h"

// VARIABLES
uint8_t score;
uint32_t motor_target = 700;
uint32_t score_delay = SCORE_DELAY;

void start_game() {
    score = 0;
}

void tick_game() {
    // Control motor
    uint32_t motor_pos = read_motor_encoder();
    int32_t u = pid_controller(motor_target, motor_pos);
    motor_controller_set_speed(u);

    // Manage score
    if (adc_value_below_threshold(300)) {
            static unsigned long last_score_time = 0;
            unsigned long current_time = 3000; //HELP

            // Check if enough time has passed since the last score
            if (current_time - last_score_time >= score_delay) {
                score++;
                printf("Score: %d\n", score);
                last_score_time = 0;
            }
        }
}