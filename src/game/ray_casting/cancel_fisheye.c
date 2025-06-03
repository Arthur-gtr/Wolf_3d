/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** cancel_fisheye
*/
#include "ray_casting.h"

void cancel_fisheye(ray_cast_t *ray_cast)
{
    if (ray_cast->side == 0)
        ray_cast->perp_wall_dist =
        (ray_cast->side_dist_x - ray_cast->delta_dist_x);
    else
        ray_cast->perp_wall_dist =
        (ray_cast->side_dist_y - ray_cast->delta_dist_y);
}
