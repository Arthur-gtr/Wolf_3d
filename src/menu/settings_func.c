/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** settings_func
*/

#include "game.h"
#include "menu.h"

void escape_set(game_handler_t *g_h)
{
    g_h->screen->act_menu = g_h->screen->last_menu;
}

void go_to_settings(game_handler_t *g_h)
{
    g_h->screen->last_menu = g_h->screen->act_menu;
    g_h->screen->act_menu = M_SETTING;
}

void max_win(game_handler_t *g_h)
{
    g_h->settings.win_mode += 1;
    g_h->settings.win_mode %= 2;
    sfRenderWindow_close(g_h->screen->win);
    sfRenderWindow_destroy(g_h->screen->win);
    if (g_h->settings.win_mode == WINM_FSCREEN)
        g_h->screen->win = sfRenderWindow_create((sfVideoMode){1920, 1080, 32},
        "wolf3d", sfFullscreen | sfClose, NULL);
    if (g_h->settings.win_mode == WINM_BIG)
        g_h->screen->win = sfRenderWindow_create((sfVideoMode){1920, 1080, 32},
        "wolf3d", sfClose, NULL);
}

void min_win(game_handler_t *g_h)
{
    g_h->settings.win_mode -= 1;
    if (g_h->settings.win_mode > 1)
        g_h->settings.win_mode = 1;
    sfRenderWindow_close(g_h->screen->win);
    sfRenderWindow_destroy(g_h->screen->win);
    if (g_h->settings.win_mode == WINM_FSCREEN)
        g_h->screen->win = sfRenderWindow_create((sfVideoMode)
            {1920, 1080, 32}, "wolf3d", sfFullscreen | sfClose, NULL);
    if (g_h->settings.win_mode == WINM_BIG)
        g_h->screen->win = sfRenderWindow_create((sfVideoMode)
        {1920, 1080, 32}, "wolf3d", sfClose, NULL);
}
