#include <stdio.h>
#include <stdarg.h>
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf-stdarg.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "can_types.h"
#include "pwm.h"
#include "adc.h"
#include "dac.h"
#include "motor_controller.h"
#include "solenoid.h"
#include "utility.h"
#include "game.h"

#include "sam.h"

int main()
{
    SystemInit();
    PMC->PMC_PCR |= PMC_PCR_EN;

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    pwm_init();
    pwm_set_dutycycle_ms(1500);

    can_setup();

    configure_uart();

    adc_init();
    solenoid_init();
    solenoid_off();
    motor_controller_init();
    motor_encoder_init();
    encoder_calibration();
    
    printf("Hello World\n");
    // encoder_reset();

    start_game();

    while (1)
    {
        tick_game();

        // CAN_MESSAGE slangemsg = {
        //     CAN_PRINTSRT_ID, 7, "slange"
        // };
        // can_send(&slangemsg, 0);

        // delay_ms(250);
        // pwm_set_position(0);
        // delay_ms(250);
        // pwm_set_position(255);

        delay_ms(30);
    }
    
}

// CAN_MESSAGE slangemsg = {
//     CAN_PRINTSRT_ID, 7, "slange"
// };
// can_send(&slangemsg, 0);

// int val = adc_read();
// printf("adc: %d\n", val);

// dac_output(2000);

// read_motor_encoder();

// int speed = (abs((i*500)%16000 - 8000)-4000)/2;
// motor_controller_set_speed(speed);

// if (i%100 == 0) solenoid_on();
// if (i%100 == 10) solenoid_off();