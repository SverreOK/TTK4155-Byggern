#include <stdio.h>
#include "oled.h"

#define MAX_CHILDREN 5

// Source u/duane11583 how to create a menu for low level system
// https://www.reddit.com/r/embedded/comments/vviwq6/whats_the_best_way_to_make_a_user_menu_on_a_tiny/
// Heavily inspired by https://github.com/johans1jo/TTK4155-Byggern/blob/master/node1/menu.c
typedef struct menu_entry {
    int number;
    const char *menu_title;
    void (*function)(void);
    struct menu_entry *parent;
    struct menu_entry *child[MAX_CHILDREN];
} menu_t, *menu_ptr;

// initialize function
menu_ptr menu_init();

// add menu
menu_ptr menu_add(menu_ptr parent, const char * text, void (*function)());

// goto menu
void menu_activate(menu_ptr menu);

// menu select/goto
menu_ptr menu_select(menu_ptr menu, int menu_depth, int element);

// test
void menu_print();

// uart print status
void uart_print_status(menu_ptr current_menu);

void show_play_game();

void show_calibrate_encoder();

void show_ping_pong();

void show_difficulty();

void show_highscore();

void show_easy();

void show_intermediate();

void show_advanced();