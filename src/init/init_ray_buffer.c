/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** ray_buffer
*/

#include "game.h"
#include "ray_casting.h"

bool init_ray_buffer(ray_cast_t *ray_cast)
{
    ray_cast->pixels = malloc(1080 * 1920 * 4);
    ray_cast->screen_text = sfTexture_create(1920, 1080);
    ray_cast->sprite_screen = sfSprite_create();
    if (ray_cast->pixels == NULL ||
        ray_cast->screen_text == NULL ||
        ray_cast->sprite_screen == NULL)
        return false;
    return true;
}
