#include <avr/io.h>

#define DDR_SPI DDRB // Source: erlendb TTK4155-Byggern-labhjelp/lab5.md github
#define DD_SS PB4
#define DD_MOSI PB5
#define DD_MISO PB6
#define DD_SCK PB7

void spi_set_ss();
void spi_clear_ss(); // :Source

void spi_init(void);
void spi_write(char cData);
char spi_read();