/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** dda_managment
*/
#include "game.h"
#include "ray_casting.h"
#include "utils.h"

void prep_dda(ray_cast_t *ray_cast, entities_t *player)
{
    if (ray_cast->raydir_x < 0){
        ray_cast->step_x = -1;
        ray_cast->side_dist_x =
        (player->coord.x - ray_cast->map_x) * ray_cast->delta_dist_x;
    } else {
        ray_cast->step_x = 1;
        ray_cast->side_dist_x = (ray_cast->map_x + 1.0 - player->coord.x)
        * ray_cast->delta_dist_x;
    }
    if (ray_cast->raydir_y < 0){
        ray_cast->step_y = -1;
        ray_cast->side_dist_y = (player->coord.y - ray_cast->map_y)
        * ray_cast->delta_dist_y;
    } else {
        ray_cast->step_y = 1;
        ray_cast->side_dist_y = (ray_cast->map_y + 1.0 - player->coord.y)
        * ray_cast->delta_dist_y;
    }
}

/*
** get l' int du pixel touché
*/
void execute_dda(ray_cast_t *ray_cast, int map[20][20])
{
    while (ray_cast->hit == 0) {
        if (ray_cast->side_dist_x < ray_cast->side_dist_y) {
            ray_cast->side_dist_x += ray_cast->delta_dist_x;
            ray_cast->map_x += ray_cast->step_x;
            ray_cast->side = 0;
        } else {
        ray_cast->side_dist_y += ray_cast->delta_dist_y;
        ray_cast->map_y += ray_cast->step_y;
        ray_cast->side = 1;
        }
        if (ray_cast->map_x < MAP_WIDTH && ray_cast->map_x >= 0 &&
            ray_cast->map_y < MAP_HEIGHT && ray_cast->map_y >= 0 &&
            IS_WALL(map[ray_cast->map_x][ray_cast->map_y]) == true)
            ray_cast->hit = 1;
    }
    if (ray_cast->map_x < MAP_WIDTH && ray_cast->map_x >= 0 &&
        ray_cast->map_y < MAP_HEIGHT && ray_cast->map_y >= 0)
        ray_cast->texture = map[ray_cast->map_x][ray_cast->map_y];
}
