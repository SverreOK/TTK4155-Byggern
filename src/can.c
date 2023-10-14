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
    mcp_setmode(MODE_LOOPBACK);
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
        message->id = mcp_read(MCP_RXB0SIDH) << 3;
        message->id |= mcp_read(MCP_RXB0SIDL) >> 5;

        message->length = mcp_read(MCP_RXB0DLC);

        for (int i = 0; i < message->length; i++)
        {
            message->data[i] = mcp_read(MCP_RXB0D0 + i);
        }
    }
    else return 0;

    return 1;
}

