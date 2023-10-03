#include "../inc/oled.h"
#include "../inc/fonts.h"
//#include <string.h>

#define OLED_COMMAND_ADDRESS 0x1000
#define OLED_DATA_ADDRESS 0x1200
#define DISPLAY_COLUMNS 128
#define DISPLAY_PAGES 8

uint8_t oled_line = 0;
uint8_t oled_col = 0;
uint8_t font_size = 5;
uint8_t inverted = 0;

void write_c(uint8_t command)
{
    uint8_t volatile * const command_reg = (uint8_t *) OLED_COMMAND_ADDRESS;
    *command_reg = command;
}

void write_d(uint8_t data)
{
    uint8_t volatile * const data_reg = (uint8_t *) OLED_DATA_ADDRESS;
    *data_reg = data;
}

FILE* oled_init() // Source: 力元電子（香港）有限公司
{
    write_c(0xae); // display off
    write_c(0xa1); //segment remap
    write_c(0xda); //common pads hardware: alternative
    write_c(0x12);
    write_c(0xc8); //common output scan direction:com63~com0
    write_c(0xa8); //multiplex ration mode:63
    write_c(0x3f);
    write_c(0xd5); //display divide ratio/osc. freq. mode
    write_c(0x80);
    write_c(0x81); //contrast control
    write_c(0x50);
    write_c(0xd9); //set pre-charge period
    write_c(0x21);
    write_c(0x20); //Set Memory Addressing Mode
    write_c(0x02);
    write_c(0xdb); //VCOM deselect level mode
    write_c(0x30);
    write_c(0xad); //master configuration
    write_c(0x00);
    write_c(0xaf); // display on

    oled_goto(0, 0);

    return fdevopen(&oled_print_f, NULL); // Test code: vfprintf(oled_file, "Hello world 6 %d", 5); (doesn't work)
}

void oled_test()
{
    oled_reset();

    oled_goto(1, 0);
    oled_print_char('A');
    oled_print_char('B');
    oled_print_char('C');
    oled_print(" Hello world ");
    inverted = 1;
    oled_print_line(6, "En linje");
}

void oled_draw_arrow(uint8_t line, uint8_t column)
{
    oled_goto(line, column);

    write_d(0b00011000);
    write_d(0b00011000);
    write_d(0b00011000);
    write_d(0b01111110);
    write_d(0b00111100);
    write_d(0b00011000);
}

void oled_reset()
{
    for (int i = 0; i < DISPLAY_PAGES; i++) 
    {
        oled_clear_line(i);
    }
    oled_home();
}
    
void oled_home() {
    oled_goto_column(0);
    oled_goto_line(0);
}

void oled_goto_line(uint8_t line) {
    oled_line = line;
    write_c(0xB0 + line);
}

void oled_goto_column(uint8_t column)
{
    oled_col = column;
    write_c(0x00 + (column & 0x0F));
    write_c(0x10 + ((column & 0xF0) >> 4));
}

void oled_goto(uint8_t line, uint8_t column)
{
    oled_goto_line(line);
    oled_goto_column(column);
}

void oled_clear_line(uint8_t line)
{
    oled_goto(line, 0);
    for (int i = 0; i < DISPLAY_COLUMNS; i++)
    {
        write_d(0);
    }
}

void oled_whitespace(uint8_t width)
{
    for (int i = 0; i < width; i++)
    {
        write_d(inverted * 0xff);
        oled_goto_column(++oled_col);
    }
}

void oled_print_char(char c)
{
    for (int i = 0; i < font_size; i++)
    {
        uint8_t data;
        
        if (font_size == 4)         data = pgm_read_byte(&(font4[c - 32][i]));
        else if (font_size == 5)    data = pgm_read_byte(&(font5[c - 32][i]));
        else                        data = pgm_read_byte(&(font8[c - 32][i]));

        write_d(data ^ (inverted * 0xff)); // XOR
    }
    oled_goto_column(oled_col += font_size);
    if (font_size==5) oled_whitespace(1);
}

int oled_print_f(char * c, FILE* f)
{
    oled_print_char(c);
    return 0;
}

void oled_print(const char text[])
{
    for (int i = 0; i < strlen(text); i++)
    {
        oled_print_char(text[i]);
    }
}

void oled_print_line(uint8_t line, const char text[])
{
    oled_goto(line, 0);
    oled_whitespace(2);
    oled_print(text);
    oled_whitespace(2);
}