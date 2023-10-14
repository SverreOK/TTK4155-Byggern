#include "mcp.h"
#include <string.h>

typedef struct message{
    uint16_t id;
    uint8_t length;
    uint8_t data[8];
} CAN_MESSAGE;

void can_interrupt_init();

void can_init();
// void can_transmit(unsigned int id, uint8_t length, uint8_t data[]);
void can_transmit(CAN_MESSAGE* message);
int can_receive(CAN_MESSAGE* message);