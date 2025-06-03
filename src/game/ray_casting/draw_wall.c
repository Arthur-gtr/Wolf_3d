/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** draw_screen
*/
#include "ray_casting.h"

/*Display the buffer of pixel how contain the wall*/
int draw_wall(ray_cast_t *ray_cast, sfRenderWindow *window)
{
    sfTexture_updateFromPixels(ray_cast->screen_text,
        ray_cast->pixels, 1920, 1080, 0, 0);
    sfSprite_setTexture(ray_cast->sprite_screen,
        ray_cast->screen_text, sfTrue);
    sfRenderWindow_drawSprite(window, ray_cast->sprite_screen, NULL);
    return 0;
}
