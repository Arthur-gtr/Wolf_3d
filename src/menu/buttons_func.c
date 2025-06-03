/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** buttons_func
*/

#include "game.h"
#include "menu.h"

void exit_game(game_handler_t *game_handler)
{
    sfRenderWindow_close(game_handler->screen->win);
}

void go_to_home(game_handler_t *g_h)
{
    g_h->screen->act_menu = M_START;
    free_game(g_h);
    sfMusic_stop(g_h->game->game_music);
    g_h->game = NULL;
}

void back_to_game(game_handler_t *g_h)
{
    g_h->screen_mode = S_GAME;
    sfMusic_stop(g_h->screen->menu_music);
    sfMusic_play(g_h->game->game_music);
}
