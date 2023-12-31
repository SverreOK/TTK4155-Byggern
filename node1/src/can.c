#include "can.h"
#include <avr/io.h>


void can_interrupt_init()
{
    DDRD &= ~(1 << PD2); //Definerer at PD2 blir input
    SREG |= (1 << 7 ); //setter INT0 til 1
    GICR |= (1 << INT0); //setter global interrupt enable til 1

    MCUCR |= (1 << ISC01) ; //setter til 1 i mcucr falling edge
    MCUCR &= ~(1 << ISC00) ; //setter til 0 i mcucr falling edge

    mcp_bit_modify(MCP_CANINTE, MCP_RX_INT, MCP_RX_INT); //aktiverer interrupt pin caninte
    //mcp_bit_modify(MCP_CANINTF, , );

}

void can_init()
{
    mcp_init();

    const uint64_t F_OSC = 16e6;
    const uint8_t PROPAG = 2;
    const uint8_t PS1 = 7;
    const uint8_t PS2 = 6; // Total of 16 TQ in one bit (1+2+6+7)
    const uint8_t SYNC = 1;
    const uint8_t NUM_TQ = PROPAG + PS1 + PS2 + SYNC;
    const uint64_t BITRATE = 125000;
    const uint8_t BRP = F_OSC/(2*NUM_TQ*BITRATE); // Yields BRP = 4

    mcp_write(MCP_CNF1, SJW4 | (BRP-1));
    mcp_write(MCP_CNF2, BTLMODE | SAMPLE_1X | ((PS1 - 1) << 3) | (PROPAG - 1));
    mcp_write(MCP_CNF3, WAKFIL_DISABLE | (PS2 - 1));

    mcp_setmode(MODE_NORMAL);
    can_interrupt_init();

}

void can_transmit(CAN_MESSAGE* message)
{
    mcp_write(TXB0SIDH, message->id >> 3); // Write id
    mcp_write(TXB0SIDL, message->id << 5);

    mcp_write(TXB0DLC, message->length); // Write data length

    for (int i = 0; i < message->length; i++) // Write data to send
    {
        mcp_write(TXB0D0 + i, message->data[i]);
    }

    mcp_request_to_send(0);
}


int can_receive(CAN_MESSAGE* message)
{
    if (mcp_read(MCP_CANINTF) & MCP_RX0IF)
    {
        message->id = mcp_read(MCP_RXB0SIDH) << 3 | mcp_read(MCP_RXB0SIDL) >> 5;

        message->length = mcp_read(MCP_RXB0DLC);

        for (int i = 0; i < message->length; i++)
        {
            message->data[i] = mcp_read(MCP_RXB0D0 + i);
        }
    }
    else return 0;

    return 1;
}

