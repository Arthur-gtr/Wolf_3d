/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** handle_player_shooting
*/

#include "game.h"

void handle_player_shooting(game_handler_t *g_h)
{
    player_t *player = g_h->game->ent->player;

    if (player->is_shooting == false)
        return;
    player->inventory->gun[player->inventory->actual_gun]->
        gun_shot(player, NULL, g_h);
}
