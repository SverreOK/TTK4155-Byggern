#include "can.h"

void can_init()
{
    mcp_init();
    mcp_setmode(MODE_LOOPBACK);
}

void can_transmit(unsigned int id, uint8_t length, uint8_t data[])
{
    
}