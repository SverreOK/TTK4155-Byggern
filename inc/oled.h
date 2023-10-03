#include <stdint.h>
#include <stdio.h>

uint8_t font_size;
uint8_t inverted;

FILE* oled_init();
void oled_reset(); // Blank screen
void oled_home(); // Pos (0, 0)
void oled_goto_line(uint8_t line);
void oled_goto_column(uint8_t column);
void oled_goto(uint8_t line, uint8_t column);
void oled_clear_line(uint8_t line); // Blanc line
void oled_print_char(char c); // Print single character at current location
int oled_print_f(char * c, FILE* f); // Modified oled_print_char() to work with printf
void oled_test();
void oled_print(const char text[]);  // Print text from current location
void oled_print_line(uint8_t line, const char text[]); // Print text at specified line
void oled_whitespace(uint8_t width); // add custon amount of whitespace. Works with inverted.