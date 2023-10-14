#include <stdint.h>
#include "mcp2515_constants.h"
#include <avr/io.h>

#define TXB0SIDH 0x31
#define TXB0SIDL 0x32
#define TXB0DLC 0x35
#define TXB0D0 0x36

uint8_t mcp_init();
void mcp_reset();
uint8_t mcp_read(uint8_t address);
void mcp_write(uint8_t address, uint8_t data);
uint8_t mcp_read_status();
void mcp_request_to_send(uint8_t regnum);
void mcp_setmode(uint8_t mode);
void mcp_bit_modify(uint8_t address, uint8_t mask , uint8_t data);
