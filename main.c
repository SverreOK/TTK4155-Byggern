//test
#define F_CPU 4915200
#define BLINK_HZ 10

#include <avr/io.h>
#include <util/delay.h>
#include "inc/uart.h"
#include "inc/xmem.h"
#include "inc/adc.h"
#include "inc/io.h"

void blinkLED();
void testUART();
void SRAM_test(void);
void print_adc();
void print_buttons();

int main(void) {
    adc_init();
    xmem_init();
    uart_init(MYUBRR);
    io_input_init();

    printf("Hallo!\n");

    while (1) {
        print_buttons();
        _delay_ms(100);
    }

    // SRAM_test();
    return 0;
}

void print_buttons()
{
    printf("Button: %i, %i, %i\n", io_read(1), io_read(2), io_read(3));
}

void print_adc()
{
    uint8_t values[4];
    adc_read_all(values);

    printf("value: %i,  %i,  %i,  %i\n", values[0], values[1], values[2], values[3]);   //, adc_read(0), adc_read(1), adc_read(2), adc_read(3));
}

void testUART1() {
    uart_init(MYUBRR);
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

void SRAM_test(void)
{
    volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
    uint16_t ext_ram_size = 0x800;
    uint16_t write_errors = 0;
    uint16_t retrieval_errors = 0;
    printf("Starting SRAM test...\n");
    // rand() stores some internal state, so calling this function in a loop will
    // yield different seeds each time (unless srand() is called before this function)
    uint16_t seed = rand();
    // Write phase: Immediately check that the correct value was stored
    srand(seed);
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = rand();
        ext_ram[i] = some_value;
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value) {
            printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
            write_errors++;
        }
    }
    // Retrieval phase: Check that no values were changed during or after the write phase
    srand(seed);
    // reset the PRNG to the state it had before the write phase
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = rand();
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value) {
            printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
            retrieval_errors++;
        }
    }
    printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}