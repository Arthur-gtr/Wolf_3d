/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** execute_ray
*/
#include "game.h"
#include "ray_casting.h"

#include <string.h>

int execute_ray(game_handler_t *game, entities_t *player)
{
    memset(game->ray_cast.pixels, 0, 1920 * 1080 * 4);
    draw_floor(player, &game->ray_cast, game->texture);
    for (int x = 0; x < 1920; x++){
        init_ray_cast(&game->ray_cast, game->game->ent->player->property, x);
        prep_dda(&game->ray_cast, player);
        execute_dda(&game->ray_cast,
            game->game->level.map[game->game->level.actual_level]);
        cancel_fisheye(&game->ray_cast);
        det_line(&game->ray_cast);
        get_text_pixel(&game->ray_cast, player);
        fill_line(&game->ray_cast, x, game->texture);
        game->ray_cast.z_buffer[x] = game->ray_cast.perp_wall_dist;
    }
    return 0;
}
