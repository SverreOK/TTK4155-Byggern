#include "motor_controller.h"
#include "sam.h"
#include "dac.h"
#include "utility.h"

#define EN_PIN PIO_PD9
#define DIR_PIN PIO_PD10

uint8_t calibrating = 0;

void motor_controller_init()
{
    dac_init();

    // Set MotorEN and MotroDIR as outputs
    // REG_PIOD_OER = PIO_PD7 | PIO_PD8; // D11 & D12 on DUE, hopefully MJ1-6 & MJ1-7 on shield

    REG_PIOD_PER |= EN_PIN | DIR_PIN;
    REG_PIOD_OER |= EN_PIN | DIR_PIN;

    REG_PIOD_SODR |= EN_PIN;
}

void motor_controller_set_speed(int32_t value) // -4096 to 4095
{
    motor_controller_set_direction(value < 0);
    dac_output(abs(value));
}

void motor_controller_set_direction(uint8_t dir)
{
    if (dir)    REG_PIOD_SODR |= DIR_PIN;
    else        REG_PIOD_CODR |= DIR_PIN;
}

void motor_encoder_init() {

    /*PIN25 = PD0 = NOT_OE
    PIN26 = PD1 = NOT_RST
    PIN27 = PD2 = SEL

    PIN33 = PC1 = DO0
    PIN34 = PC2 = DO1
    PIN35 = PC3 = DO2
    PIN36 = PC4 = DO3
    PIN37 = PC5 = DO4
    PIN38 = PC6 = DO5
    PIN39 = PC7 = DO6
    PIN40 = PC8 = DO7*/

    // !OE - ENCODER OUTPUT ENABLE (inv)
    // !RST - ENCODER RESET (inv)
    // SEL - ENCODER SELECT LOW BYTE
    // DOn - ENCODER BYTE OUTPUT (2-9)

    REG_PIOD_PER |= PIO_PD0 | PIO_PD1 | PIO_PD2;

    REG_PIOD_OER |= PIO_PD0 | PIO_PD1 | PIO_PD2;

    REG_PIOD_CODR |= PIO_PD1;
    delay_us(20);
    REG_PIOD_SODR |= PIO_PD1;

    // Encoder outputs here
    REG_PIOC_PER |= PIO_PC1 |
                    PIO_PC2 |
                    PIO_PC3 |
                    PIO_PC4 |
                    PIO_PC5 |
                    PIO_PC6 |
                    PIO_PC7 |
                    PIO_PC8;

    REG_PIOC_ODR |= PIO_PC1 |
                    PIO_PC2 |
                    PIO_PC3 |
                    PIO_PC4 |
                    PIO_PC5 |
                    PIO_PC6 |
                    PIO_PC7 |
                    PIO_PC8;

    REG_PIOC_PUDR |= PIO_PC1 |
                     PIO_PC2 |
                     PIO_PC3 |
                     PIO_PC4 |
                     PIO_PC5 |
                     PIO_PC6 |
                     PIO_PC7 |
                     PIO_PC8;
}

uint16_t read_motor_encoder() {
    REG_PMC_PCER0 |= PMC_PCER0_PID13;
    //Set !OE low
    REG_PIOD_CODR |= PIO_PD0;
    //Set SEL low
    REG_PIOD_CODR |= PIO_PD2;
    //Delay about 20 microseconds
    delay_us(20);
    
    //Read MJ2 to get high byte
    uint8_t msb = (uint8_t) ((REG_PIOC_PDSR & 0x1FE) >> 1);

    //Set SEL high
    REG_PIOD_SODR |= PIO_PD2;
    // Delay about 20 microseconds
    delay_us(20);

    uint8_t lsb = (uint8_t) ((REG_PIOC_PDSR & 0x1FE) >> 1);

    //SET !OE high
    REG_PIOD_SODR |= PIO_PD0;

    // Combine uint8_t to uint16_t
    uint16_t encoder_val = ((uint16_t)msb << 8) | lsb;

    // check edges
    if (encoder_val > 2000) {
        encoder_val = 0;
    }
    else if (encoder_val < 2000 && encoder_val > 1400) {
        encoder_val = 1400;
    }

    // printf("Encoder Value: %d\n", encoder_val);
    return encoder_val;
}

void encoder_reset() {
    REG_PIOD_CODR |= PIO_PD1;
    delay_us(20);
    REG_PIOD_SODR |= PIO_PD1;
}

void encoder_calibration() {
    //go to the left for 1 second
    calibrating = 1;
    motor_controller_set_speed(-3000);
    delay_ms(1000);
    motor_controller_set_speed(0);
    encoder_reset();
    calibrating = 0;
    return;
}

