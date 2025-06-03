/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** init_ray_casting
*/
#include "game.h"
#include "ray_casting.h"

void init_ray_cast(ray_cast_t *ray_cast, entities_t *player, int x)
{
    ray_cast->camera_x = 2 * x / (double)(1920) - 1;
    ray_cast->raydir_x = player->dir.x + player->plan.x * ray_cast->camera_x;
    ray_cast->raydir_y = player->dir.y + player->plan.y * ray_cast->camera_x;
    ray_cast->map_x = (int)(player->coord.x);
    ray_cast->map_y = (int)(player->coord.y);
    ray_cast->delta_dist_x = (ray_cast->raydir_x == 0) ? 1e30 :
        fabs(1 / ray_cast->raydir_x);
    ray_cast->delta_dist_y = (ray_cast->raydir_y == 0) ? 1e30 :
        fabs(1 / ray_cast->raydir_y);
    ray_cast->hit = 0;
}
