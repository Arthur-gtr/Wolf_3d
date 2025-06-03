/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** sound_settings
*/

#include "game.h"
#include "menu.h"

void min_sound(game_handler_t *g_h)
{
    g_h->settings.sound_volume -= 5.0;
    if (g_h->settings.sound_volume < 0.0)
        g_h->settings.sound_volume = 0.0;
    for (int i = 0; g_h->sound[i]; i++)
        sfSound_setVolume(g_h->sound[i]->sound, g_h->settings.sound_volume);
}

void max_sound(game_handler_t *g_h)
{
    g_h->settings.sound_volume += 5.0;
    if (g_h->settings.sound_volume > 100.0)
        g_h->settings.sound_volume = 100.0;
    for (int i = 0; g_h->sound[i]; i++)
        sfSound_setVolume(g_h->sound[i]->sound, g_h->settings.sound_volume);
}

void min_music(game_handler_t *g_h)
{
    g_h->settings.music_volume -= 5.0;
    if (g_h->settings.music_volume < 0.0)
        g_h->settings.music_volume = 0.0;
    sfMusic_setVolume(g_h->screen->menu_music, g_h->settings.music_volume);
    if (g_h->game)
        sfMusic_setVolume(g_h->game->game_music, g_h->settings.music_volume);
}

void max_music(game_handler_t *g_h)
{
    g_h->settings.music_volume += 5.0;
    if (g_h->settings.music_volume > 100.0)
        g_h->settings.music_volume = 100.0;
    sfMusic_setVolume(g_h->screen->menu_music, g_h->settings.music_volume);
    if (g_h->game)
        sfMusic_setVolume(g_h->game->game_music, g_h->settings.music_volume);
}
