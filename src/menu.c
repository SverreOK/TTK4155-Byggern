#include "menu.h"
#include "joystick.h"
#include "oled.h"
#include <stdlib.h>
#include <stdio.h>
#include <avr/pgmspace.h>

const char main_menu[] = "Main menu";
const char ping_pong[] = "PingPong";
const char difficulty[] = "Difficulty";
const char easy[] = "EASY";
const char intermediate[] = "MEDIUM";
const char advanced[] = "ADVANCED";
const char highscore[] = "Highscore";

// Source u/duane11583 how to create a menu for low level system
// https://www.reddit.com/r/embedded/comments/vviwq6/whats_the_best_way_to_make_a_user_menu_on_a_tiny/
menu_ptr menu_init(menu_type_t) {
    menu_ptr menu = malloc(sizeof(menu_t));
    menu->menu_title = main_menu;
    clear_children(menu);

    menu_ptr menu_ping_pong = menu_add(menu, ping_pong, &show_ping_pong);
    menu_ptr menu_difficulty = menu_add(menu, difficulty, &show_difficulty);
    menu_ptr menu_highscore = menu_add(menu, highscore, &show_highscore);

    menu_ptr menu_easy = menu_add(menu_difficulty, easy, &show_easy);
    menu_ptr menu_intermediate = menu_add(menu_difficulty, intermediate, &show_intermediate);
    menu_ptr menu_advanced = menu_add(menu_difficulty, advanced, &show_advanced);

    return menu;
}

void menu_activate(menu_ptr menu) {
    int depth_direction = 0;
    int element = 0;
    menu_ptr current_menu = menu;

    while (1) {
        menu_ptr old_menu = current_menu;

        current_menu = menu_select(current_menu, depth_direction, element);
        depth_direction = 0;

        joystick_poll();

        joystick_action direction = joystick_get_action();

        switch (direction) {
            case UP:
                if (element > 0) {
                    element--;
                }
                oled_reset();
                break;

            case DOWN:
                if (current_menu->child[element+1] != NULL) {
                    element++;
                }
                oled_reset();
                break;

            case LEFT:
                if (current_menu == menu) {
                    depth_direction = 0;
                }
                else {
                    depth_direction = -1;
                }
                oled_reset();
                break;

            case RIGHT:
            case PRESS:
                depth_direction = 1;
                oled_reset();
                break;
            
            case NEUTRAL:
                break;
        }
        //printf("Exited while \n");
    }
}

menu_ptr menu_add(menu_ptr parent, const char * menu_title, void (*function)()) {
    menu_ptr child = malloc(sizeof(menu_t));
    child -> menu_title = menu_title;
    child -> function = function;
    child -> parent = parent;
    clear_children(child);

    int i = 0;
    while (parent->child[i] != NULL) {
        i++;
    }
    parent->child[i] = child;

    return child;
}

menu_ptr menu_select (menu_ptr current_menu, int menu_depth, int element) {
    if (menu_depth < 0) {
        if (current_menu->parent != NULL) {
            current_menu = current_menu->parent;
        }
    }
    if (menu_depth > 0) {
        if (current_menu->child[0] != NULL) {
            current_menu = current_menu->child[element];
        }
    }

    if (current_menu->function != NULL) {
        current_menu->function();
        //return current_menu;
    }

    //clear screen
    
    int i = 0;
    while (current_menu -> child[i] != NULL) {
        //oled stuff
        if (i == element) inverted = 1;
        oled_print_line(i, current_menu->child[i]->menu_title);
        inverted = 0;
        i++;
    }
    return current_menu;
}

void clear_children(menu_ptr menu)
{
    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        menu->child[i] = NULL;
    }
}

// menu functions
void show_ping_pong() {
    printf("Selected Ping Pong!\n");
    oled_reset();
    inverted = 0;
    oled_goto(2, 3*8);
    oled_print("PING!");
    oled_goto(4, 6*8);
    oled_print("PONG!!");
}

void show_difficulty() {
    printf("Selected Ping Pong!\n");
}

void show_highscore() {
    printf("Selected High Scor!\n");
    oled_reset();
    inverted = 0;
    oled_goto(2, 3*8);
    oled_print("High!");
    oled_goto(4, 6*8);
    oled_print("Score!!");
}

void show_easy() {
    printf("Selected Easy Mode!\n");
    oled_reset();
    inverted = 0;
    oled_goto(2, 3*8);
    oled_print("EASY!");
    oled_goto(4, 6*8);
    oled_print("MODE!!");
}

void show_intermediate() {
    printf("Selected Intermediate Mode!\n");
    oled_reset();
    inverted = 0;
    oled_goto(2, 3*8);
    oled_print("Intermediate!");
    oled_goto(4, 6*8);
    oled_print("Mode!!");
}

void show_advanced() {
    printf("Selected Advanced Mode!\n");
    oled_reset();
    inverted = 0;
    oled_goto(2, 3*8);
    oled_print("Advanced!");
    oled_goto(4, 6*8);
    oled_print("Mode!!");
}