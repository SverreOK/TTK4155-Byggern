#include "mcp.h"
#include "spi.h"

uint8_t mcp_init() // Source: Lab Lecture 3 (but modified)
{
    spi_init() ; // Initialize SPI
    mcp_reset() ; // Send reset - command
    // Self - test
    uint8_t value = mcp_read( MCP_CANSTAT);
    if (( value & MODE_MASK ) != MODE_CONFIG ) {
        printf("MCP2515 is NOT in configuration mode after reset!\n");
        return 1;
    }
    return 0;
}

uint8_t mcp_read(uint8_t address)
{
    uint8_t result;
    spi_clear_ss(); // Select CAN-controller
    spi_write(MCP_READ); // Send read instruction
    spi_write(address); // Send address
    result = spi_read(); // Read result
    spi_set_ss(); // Deselect CAN-controller
    return result; 
} // :Source

void mcp_write(uint8_t address, uint8_t data)
{
    uint8_t result;
    spi_clear_ss(); // Select CAN-controller
    spi_write(MCP_WRITE); // Send write instruction
    spi_write(address); // Send address
    spi_write(data); //send data atleast 1 byte
    spi_set_ss(); // Deselect CAN-controller
} 

void mcp_reset()
{
    spi_clear_ss();
    spi_write(MCP_RESET);
    spi_set_ss();
}

void mcp_bit_modify(uint8_t address, uint8_t mask , uint8_t data)
{
    spi_clear_ss();
    spi_write(MCP_BITMOD);
    spi_write(address);
    spi_write(mask);
    spi_write(data);
    spi_set_ss();
}

uint8_t mcp_read_status()
{
    spi_clear_ss();
    spi_write(MCP_READ_STATUS);
    uint8_t status = spi_read();
    spi_set_ss();
    return status;
}

void mcp_request_to_send(uint8_t regnum)
{
    spi_clear_ss();
    if (regnum == 0)        spi_write(MCP_RTS_TX0);
    else if (regnum == 1)   spi_write(MCP_RTS_TX1);
    else if (regnum == 2)   spi_write(MCP_RTS_TX2);
    else                    printf("Invalid regnum (%d) for mcp_request_to_send()\n", regnum);
    spi_set_ss();
}

void mcp_setmode(uint8_t mode)
{
    mcp_bit_modify(MCP_CANCTRL, MODE_MASK, mode);

}