#include "score.h"
#include "adc.h"

#include "../uart_and_printf/printf-stdarg.h"

const int ir_threshold = 600;
const float filter_coefficient = 0.5; // For low pas filtering the IR sensor
int ir_filtered = 0;
uint8_t new_goal = 0;
uint8_t scoring = 1;

void score_init()
{
    adc_init();
}

void score_update()
{
    int ir_value = adc_read();
    ir_filtered += (int)(filter_coefficient*(ir_value - ir_filtered));

    if (ir_filtered < ir_threshold) // score
    {
        if (!scoring)
        {
            scoring = 1;
            new_goal++;
        }
    }
    else scoring = 0;
}

int score_new_goal()
{
    int val = new_goal;
    new_goal = 0;
    return val;
}