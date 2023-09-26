#include <stdio.h>
#include "oled.h"

// Source u/duane11583 how to create a menu for low level system
// https://www.reddit.com/r/embedded/comments/vviwq6/whats_the_best_way_to_make_a_user_menu_on_a_tiny/
typedef struct menu_entry {
    int number;
    char *menu_title;
    void (*function);
    struct menu_entry *parent;
    struct Menu * child[5];
} menu_t, *menu_ptr;