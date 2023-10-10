#include <stdint.h>
#include "mcp2515_constants.h"
#include <avr/io.h>

uint8_t mcp_init();
void mcp_reset();
uint8_t mcp_read(uint8_t address);
void mcp_write(uint8_t address, uint8_t data);
uint8_t mcp_read_status();
void mcp_request_to_send(uint8_t regnum);
void mcp_setmode(uint8_t mode);
