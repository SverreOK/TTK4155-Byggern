//test
#define F_CPU 4915200
#define BLINK_HZ 10

#include <avr/io.h>
#include <util/delay.h>
#include "inc/uart.h"
#include "inc/xmem.h"
#include "inc/adc.h"
#include "inc/io.h"
#include "inc/utils.h"
#include "inc/oled.h"
#include "joystick.h"
#include "menu.h"
#include "can.h"

#include <avr/interrupt.h>

void blinkLED();
void testUART();
void print_adc();
void print_buttons();

int main(void) {
    adc_init();
    xmem_init();
    uart_init(MYUBRR);
    io_input_init();
    can_init();
    oled_init();
    joystick_calibrate();

    printf("Hallo!\n");

    oled_print_line(3, "Running SRAM test...");
    SRAM_test();


    oled_reset();

    //menu_activate(menu_init());


    while (1) {

        CAN_MESSAGE ratfrog = {
            1, 3, "rat"
        };

        can_transmit(&ratfrog);
        _delay_ms(1);

        CAN_MESSAGE ratfrog2 = {
            2, 4, "tnt"
        };

        can_transmit(&ratfrog2);
        _delay_ms(1);

        CAN_MESSAGE ratfrog3 = {
            3, 5, "tog"
        };

        can_transmit(&ratfrog3);
        _delay_ms(1);
        
    }

    // SRAM_test();
    return 0;
}

void print_buttons()
{
    printf("Button: %i, %i, %i,  ", io_read(1), io_read(2), io_read(3));
}

void print_adc()
{
    uint8_t values[4];
    adc_read_all(values);

    printf("value: %i,  %i,  %i,  %i\n", values[0], values[1], values[2], values[3]);   //, adc_read(0), adc_read(1), adc_read(2), adc_read(3));
}

void testUART1() {
    sei();
    while(1) {
        printf("Hello world\n");
        blinkLED();
    }
}

void testUART2() {
    FILE* f = uart_init(MYUBRR);
    while(1) {
        const char received_char = uart_receive(f);
        printf("%c\n", received_char);
        blinkLED();
    }
}

void testXMEM() {
    xmem_init();
    int volatile * const p_reg = (int *) 0x0F0F; //0b0001001100110011;
    *p_reg = 0x5555;
    while (1) {}
}

void blinkLED() {
    DDRA |= (1 << PA0);

    PORTA |= (1 << PA0);
    _delay_ms(1000/BLINK_HZ/2);
    PORTA &= ~(1 << PA0);
    _delay_ms(1000/BLINK_HZ/2);
    // while (1) {
    // }
}

ISR(INT0_vect) 
{
    printf("Interrupt\n");

    CAN_MESSAGE* recieved_message = malloc(sizeof(CAN_MESSAGE));
    if (can_receive(recieved_message))
    {
        printf("Recieved: %c%c%c%c id: %d len: %d\n", recieved_message->data[0], recieved_message->data[1], recieved_message->data[2], recieved_message->data[3], recieved_message->id, recieved_message->length);
    }
    else
    {
        printf("Failed to receive");
    }

    mcp_bit_modify(MCP_CANINTF, MCP_RX0IF | MCP_RX1IF, 0);
    free(recieved_message);
    
}