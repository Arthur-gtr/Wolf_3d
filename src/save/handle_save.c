/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** handle_save1
*/

#include "game.h"
#include "init.h"

void handle_save1(game_handler_t *g_h)
{
    sfMusic_pause(g_h->screen->menu_music);
    if (!init_game(g_h, "./save_f/save_1/"))
        return;
    save_game(g_h->game, g_h, false);
    g_h->screen_mode = S_GAME;
    g_h->game->have_been_f = false;
    return;
}

void handle_save2(game_handler_t *g_h)
{
    sfMusic_pause(g_h->screen->menu_music);
    if (!init_game(g_h, "./save_f/save_2/"))
        return;
    save_game(g_h->game, g_h, false);
    g_h->screen_mode = S_GAME;
    g_h->game->have_been_f = false;
    return;
}

void handle_save3(game_handler_t *g_h)
{
    sfMusic_pause(g_h->screen->menu_music);
    if (!init_game(g_h, "./save_f/save_3/"))
        return;
    if (g_h->game->have_been_f)
        save_game(g_h->game, g_h, false);
    g_h->screen_mode = S_GAME;
    g_h->game->have_been_f = false;
    return;
}
