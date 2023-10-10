#include "spi.h"

void spi_set_ss()
{
    PORTB |= (1<<DD_SS);
}

void spi_clear_ss()
{
    PORTB &= ~(1<<DD_SS);
}

// Source: ATmega162 datasheet
void spi_init(void)
{
    /* Set MOSI and SCK output, all others input */
    DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

    spi_set_ss();
}

void spi_write(char cData)
{
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF))) {}
}
// :Source

char spi_read()
{
    SPDR = 0b01001101; // Dummy data to sent

    while(!(SPSR & (1<<SPIF))) {}
    
    return SPDR;
}