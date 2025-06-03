/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** menu
*/

#ifndef MENU_H_
    #define MENU_H_
    #include "call_csfml.h"
    #include "utils.h"
    #include <stdbool.h>
    #define M_START 0
    #define M_PAUSE 1
    #define M_SETTING 2
    #define M_GO 3
    #define M_END 4
    #define NB_MENU 5
typedef struct game_handler_s game_handler_t;

typedef struct boutons_s {
    img_t *released;
    sfRectangleShape *press;
    void (*action)(game_handler_t *);
} bouton_t;

typedef struct menu_s {
    img_t *background;
    sfText *text;
    list_t *boutons;
    node_t *actual_bouton;
} menu_t;

bool init_start_menu(menu_t *menu, game_handler_t *game_h);
bool init_pause_menu(menu_t *menu, game_handler_t *game_h);
bool init_settings_menu(menu_t *menu, game_handler_t *game_h);
bool init_end_menu(menu_t *menu, game_handler_t *game_h);
bool init_go_menu(menu_t *menu, game_handler_t *game_h);
void min_sound(game_handler_t *g_h);
void max_sound(game_handler_t *g_h);
void max_music(game_handler_t *g_h);
void min_music(game_handler_t *g_h);
void max_win(game_handler_t *g_h);
void min_win(game_handler_t *g_h);
void escape_set(game_handler_t *g_h);
void go_to_settings(game_handler_t *g_h);
void exit_game(game_handler_t *game_handler);
void back_to_game(game_handler_t *g_h);
void go_to_home(game_handler_t *g_h);
void handle_save1(game_handler_t *g_h);
void handle_save2(game_handler_t *g_h);
void handle_save3(game_handler_t *g_h);
void handle_menu_event(menu_t *menu, game_handler_t *g_h, sfUint8 controller);

#endif /* !MENU_H_ */
