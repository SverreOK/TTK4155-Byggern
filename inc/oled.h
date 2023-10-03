#include <stdint.h>
#include <stdio.h>

uint8_t font_size;
uint8_t inverted;

FILE* oled_init();
void oled_reset();
void oled_home();
void oled_goto_line(uint8_t line);
void oled_goto_column(uint8_t column);
void oled_goto(uint8_t line, uint8_t column);
void oled_clear_line(uint8_t line);
void oled_pos(uint8_t row, uint8_t column);
void oled_print_char(char c);
int oled_print_f(char * c, FILE* f);
void oled_test();
void oled_print(const char text[]);
void oled_print_line(uint8_t line, const char text[]);