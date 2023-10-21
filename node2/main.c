#include <stdio.h>
#include <stdarg.h>
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf-stdarg.h"
#include "can_controller.h"
#include "can_interrupt.h"

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

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    // const uint8_t BRP = 10;
    // can_init_def_tx_rx_mb(0x165 | ((BRP - 1) << CAN_BR_BRP_Pos));

    const uint8_t PPG = 2;
    const uint8_t PS1 = 7;
    const uint8_t PS2 = 6; // Total of 16 TQ in one bit (1+2+6+7)
    const uint8_t SJW = 4;
    const uint8_t BRP = 2;

    const uint32_t CAN_RB = ((PS2-1) << CAN_BR_PHASE1_Pos)
                          | ((PS1-1) << CAN_BR_PHASE2_Pos)
                          | ((PPG-1) << CAN_BR_PROPAG_Pos)
                          | ((SJW-1) << CAN_BR_SJW_Pos)
                          | ((BRP-1) << CAN_BR_BRP_Pos);
    can_init_def_tx_rx_mb(CAN_RB);

    configure_uart();
    printf("Hello World\n");

    // Pins mapping: https://docs.arduino.cc/hacking/hardware/PinMappingSAM3X
    // Set pin 42 (PA15) as an output
    REG_PIOA_OER = PIO_PA19 | PIO_PA20;

    while (1)
    {
        // // Set pin 42 (PA15) to HIGH
        // REG_PIOA_SODR = PIO_PA19 | PIO_PA20;

        // // You can add a delay here if you want to keep it high for a specific period
        // // For example: 
        // delay_ms(500);

        // // To set it low:
        // REG_PIOA_CODR = PIO_PA19 | PIO_PA20;

        // // You can add another delay if needed
        // // For example: 
        // delay_ms(500);

        CAN0_Handler();
    }
    
}