/*
** EPITECH PROJECT, 2025
** bootstrap
** File description:
** launch_game
*/
#include "game.h"
#include <stdbool.h>
#include "controller.h"

sfUint8 get_controller_button(void)
{
    sfUint8 controller = 0;

    if (check_cross() == true)
        controller |= DOWN;
    if (check_triangle() == true)
        controller |= UP;
    if (check_square() == true)
        controller |= LEFT;
    if (check_circle() == true)
        controller |= RIGHT;
    return controller;
}

/*
** Récupère l evenement du jeu actuel
** et set la clock de fram rate
*/
bool need_refresh(game_handler_t *game_handler)
{
    game_handler->general_clock.time
        = sfClock_getElapsedTime(game_handler->general_clock.clock);
    game_handler->general_clock.time_as_micro_second
        = sfTime_asMicroseconds(game_handler->general_clock.time);
    if (game_handler->general_clock.time_as_micro_second > 16.666){
        sfClock_restart(game_handler->general_clock.clock);
        return true;
    }
    return false;
}

void handle_event(game_handler_t *g_h)
{
    sfEvent e;
    sfUint8 controller = 0;

    while (sfRenderWindow_pollEvent(g_h->screen->win, &e)){
        if (need_refresh_clock(&g_h->controller.time, 0.01)){
            controller = get_left_stick();
            g_h->controller.control = get_controller_button();
        }
        g_h->event = &e;
        if (g_h->screen_mode == S_MENU && (g_h->event->type == sfEvtKeyPressed
            || g_h->controller.control != 0 || controller != 0))
            handle_menu_event(&g_h->screen->menu[g_h->screen->act_menu],
            g_h, controller);
        if (g_h->screen_mode == S_GAME)
            handle_game_event(g_h);
        if (e.type == sfEvtClosed && g_h->screen->act_menu != M_PAUSE)
            sfRenderWindow_close(g_h->screen->win);
    }
}

int launch_game(game_handler_t *game_handler)
{
    sfRenderWindow_setFramerateLimit(game_handler->screen->win, 60);
    while (sfRenderWindow_isOpen(game_handler->screen->win)){
        if (need_refresh(game_handler) == false)
            continue;
        handle_event(game_handler);
        sfRenderWindow_clear(game_handler->screen->win, sfBlack);
        choose_window_mode(game_handler);
        sfRenderWindow_display(game_handler->screen->win);
    }
    return 0;
}
