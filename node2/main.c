#include <stdio.h>
#include <stdarg.h>
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf-stdarg.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "can_types.h"
#include "pwm.h"
#include "adc.h"

#include "sam.h"

void delay_ms(uint32_t milliseconds) {
    volatile uint32_t i;
    uint32_t cycles = milliseconds * (SystemCoreClock / 1000 / 14);

    for (i = 0; i < cycles; i++) {
        __NOP(); // This is a no-operation instruction
    }
}


int main()
{
    SystemInit();

    pwm_init();    

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer



    const uint8_t PPG = 2;
    const uint8_t PS1 = 7;
    const uint8_t PS2 = 6;
    const uint8_t SJW = 4;
    const uint8_t BRP = 42; // Calculation: It works ¯\_(ツ)_/¯

    const uint32_t CAN_RB = ((PS2-1) << CAN_BR_PHASE1_Pos)
                          | ((PS1-1) << CAN_BR_PHASE2_Pos)
                          | ((PPG-1) << CAN_BR_PROPAG_Pos)
                          | ((SJW-1) << CAN_BR_SJW_Pos)
                          | ((BRP-1) << CAN_BR_BRP_Pos);
    can_init_def_tx_rx_mb(CAN_RB);

    configure_uart();
    printf("Hello World\n");

    while (1)
    {
        // CAN_MESSAGE slangemsg = {
        //     CAN_PRINTSRT_ID, 6, "slange"
        // };

        // can_send(&slangemsg, 0);

        int val = adc_read();

        printf("adc: %d\n", val);

        delay_ms(300);
    }
    
}