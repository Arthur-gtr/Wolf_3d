/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** player_interaction
*/

#include "game.h"
#include <time.h>
#include "ray_casting.h"
/*
return the time of clock
in millisecond
*/

sfInt32 get_milisc_clock(time_management_t *time_manage, int restart)
{
    time_manage->time = sfClock_getElapsedTime(time_manage->clock);
    time_manage->time_as_milli_sc = sfTime_asMilliseconds(time_manage->time);
    if (restart == RST_CLOCK)
        sfClock_restart(time_manage->clock);
    return time_manage->time_as_milli_sc;
}

static
void new_moove_player(player_t *player, hud_t *hud, sfInt32 tim_mili,
    int map[20][20])
{
    sfUint8 controller = get_left_stick();

    if (sfKeyboard_isKeyPressed(sfKeyZ) || controller & UP){
        new_moove_up(player->property, tim_mili, map);
        player->inventory->gun[player->inventory->actual_gun]->img->pos.y
        += hud->to_move;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS) || controller & DOWN)
        new_moove_down(player->property, tim_mili, map);
    if (sfKeyboard_isKeyPressed(sfKeyQ) || controller & LEFT)
        new_moove_left(player->property, tim_mili, map);
    if (sfKeyboard_isKeyPressed(sfKeyD) || controller & RIGHT)
        new_moove_right(player->property, tim_mili, map);
}

void player_interaction(entities_t *player, game_handler_t *g_h)
{
    sfInt32 tim_mili = get_milisc_clock(&player->clock, RST_CLOCK);

    new_moove_player(g_h->game->ent->player
        , g_h->game->hud
        , tim_mili
        , g_h->game->level.map[g_h->game->level.actual_level]);
    new_rotate_player(player, 0.003, tim_mili);
}
