/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** launch_shoot
*/
#include "game.h"

bool launch_p_shoot(inventory_t *inv, float millisec_to_wait,
    game_handler_t *g_h, size_t token_sound)
{
    inv->clock_shoot.time = sfClock_getElapsedTime(inv->clock_shoot.clock);
    inv->clock_shoot.time_as_mili =
        sfTime_asMilliseconds(inv->clock_shoot.time);
    if (inv->clock_shoot.time_as_mili < millisec_to_wait)
        return false;
    if (inv->gun[inv->actual_gun]->magazine > 0 &&
        inv->actual_gun != W_ID_KNIFE)
        inv->gun[inv->actual_gun]->magazine--;
    else if (inv->actual_gun != W_ID_KNIFE)
        return false;
    g_h->game->hud->anim = true;
    sfClock_restart(inv->clock_shoot.clock);
    sfSound_play(get_sound(g_h->sound, token_sound));
    return true;
}

bool launch_e_shoot(ennemies_t *en, float millisec_to_wait,
    game_handler_t *g_h, size_t token_sound)
{
    en->clock_shoot.time = sfClock_getElapsedTime(en->clock_shoot.clock);
    en->clock_shoot.time_as_mili = sfTime_asMilliseconds(en->clock_shoot.time);
    if (en->clock_shoot.time_as_mili < millisec_to_wait)
        return false;
    sfClock_restart(en->clock_shoot.clock);
    sfSound_play(get_sound(g_h->sound, token_sound));
    return true;
}
