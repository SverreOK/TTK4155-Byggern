#include "menu.h"
#include "joystick.h"
#include "oled.h"
#include <stdlib.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include "can.h"
#include "can_types.h"
#include <util/delay.h>

const char main_menu[] = "Main menu";

const char play_game[] = "Play game";
const char calibrate_encoder[] = "Calibrate encoder";

// const char ping_pong[] = "PingPong";
// const char difficulty[] = "Difficulty";
// const char easy[] = "EASY";
// const char intermediate[] = "MEDIUM";
// const char advanced[] = "ADVANCED";
// const char highscore[] = "Highscore";

// Source u/duane11583 how to create a menu for low level system
// https://www.reddit.com/r/embedded/comments/vviwq6/whats_the_best_way_to_make_a_user_menu_on_a_tiny/

// Heavily inspired by https://github.com/johans1jo/TTK4155-Byggern/blob/master/node1/menu.c
menu_ptr menu_init(menu_type_t) {
    menu_ptr menu = malloc(sizeof(menu_t));
    menu->menu_title = main_menu;
    clear_children(menu);

    menu_ptr menu_play_game = menu_add(menu, play_game, &show_play_game);
    menu_ptr menu_calibrate_encoder = menu_add(menu, calibrate_encoder, &show_calibrate_encoder);

    // menu_ptr menu_ping_pong = menu_add(menu, ping_pong, &show_ping_pong);
    // menu_ptr menu_difficulty = menu_add(menu, difficulty, &show_difficulty);
    // menu_ptr menu_highscore = menu_add(menu, highscore, &show_highscore);

    // menu_ptr menu_easy = menu_add(menu_difficulty, easy, &show_easy);
    // menu_ptr menu_intermediate = menu_add(menu_difficulty, intermediate, &show_intermediate);
    // menu_ptr menu_advanced = menu_add(menu_difficulty, advanced, &show_advanced);

    return menu;
}

void menu_activate(menu_ptr menu) {
    int8_t dir = 0;
    uint8_t element = 0;
    menu_ptr current_menu = menu;
    draw_menu(current_menu, element);

    while (1)
    {
        joystick_poll_action();
        joystick_action direction = joystick_get_action();

        dir = 0;
        uint8_t redraw = 0;

        switch (direction) {
            case UP:
                if (element > 0) {
                    element--;
                }
                redraw = 1;
                break;

            case DOWN:
                if (current_menu->child[element+1] != NULL) {
                    element++;
                }
                redraw = 1;
                break;

            case LEFT:
                if (current_menu == menu) {
                    dir = 0;
                }
                else {
                    dir = -1;
                }
                redraw = 1;
                break;

            case RIGHT:
            case PRESS:
                dir = 1;
                redraw = 1;
                break;
            
            case NEUTRAL:
                break;
        }

        current_menu = menu_select(current_menu, dir, element);

        if (redraw)
        {
            draw_menu(current_menu, element);
        }
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

menu_ptr menu_select (menu_ptr current_menu, int menu_depth, int element){
    if ((menu_depth < 0) && (current_menu->parent != NULL)){
        current_menu = current_menu->parent;
    }
    if ((menu_depth > 0) && (current_menu->child[0] != NULL)){
        current_menu = current_menu->child[element];
    }

    if (current_menu->function != NULL){
        current_menu->function();
    }
    
    return current_menu;
}

void draw_menu(menu_ptr menu, uint8_t cursor)
{
    font_size = 5;
    inverted = 0;
    
    oled_reset();
    int i = 0;
    while (menu -> child[i] != NULL) {
        //oled stuff
        if (i == cursor) inverted = 1;
        oled_print_line(i, menu->child[i]->menu_title);
        inverted = 0;
        i++;
    }
}

void clear_children(menu_ptr menu)
{
    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        menu->child[i] = NULL;
    }
}

// MENU FUNCTIONS
void show_play_game() {
    oled_reset();
    font_size = 8;
    inverted = 0;
    oled_goto(3, 4*8);
    oled_print("Playing!");

    uint8_t slider_R = adc_read(2);
    uint8_t slider_L = adc_read(3);
    uint8_t flat_btn = io_read(3);
    CAN_MESSAGE joymsg = {
        CAN_JOYSTICK_ID, 3, {slider_L, slider_R, flat_btn}
    };
    can_transmit(&joymsg);
    _delay_ms(10);
}

void show_calibrate_encoder() {
    oled_reset();
    font_size = 8;
    inverted = 0;
    oled_goto(3, 0*8);
    oled_print("Calibrating...");

    CAN_MESSAGE calmsg = {
        CAN_CALIBRATION_ID, 1, 0
    };
    can_transmit(&calmsg);
    _delay_ms(10);
}

// void show_ping_pong() {
//     printf("Selected Ping Pong!\n");
//     oled_reset();
//     font_size = 8;
//     inverted = 0;
//     oled_goto(2, 3*8);
//     oled_print("PING!");
//     oled_goto(4, 6*8);
//     oled_print("PONG!!");
// }

// void show_difficulty() {
//     printf("Selected Ping Pong!\n");
// }

// void show_highscore() {
//     printf("Selected High Scor!\n");
//     oled_reset();
//     font_size = 8;
//     inverted = 0;
//     oled_goto(2, 3*8);
//     oled_print("High!");
//     oled_goto(4, 6*8);
//     oled_print("Score!!");
// }

// void show_easy() {
//     printf("Selected Easy Mode!\n");
//     oled_reset();
//     font_size = 8;
//     inverted = 0;
//     oled_goto(2, 3*8);
//     oled_print("EASY!");
//     oled_goto(4, 6*8);
//     oled_print("MODE!!");
// }

// void show_intermediate() {
//     printf("Selected Intermediate Mode!\n");
//     oled_reset();
//     font_size = 8;
//     inverted = 0;
//     oled_goto(2, 3*8);
//     oled_print("Intermediate!");
//     oled_goto(4, 6*8);
//     oled_print("Mode!!");
// }

// void show_advanced() {
//     printf("Selected Advanced Mode!\n");
//     oled_reset();
//     font_size = 8;
//     inverted = 0;
//     oled_goto(2, 3*8);
//     oled_print("Advanced!");
//     oled_goto(4, 6*8);
//     oled_print("Mode!!");
// }