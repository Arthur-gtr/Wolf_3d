/*
** EPITECH PROJECT, 2025
** B-MUL
** File description:
** create_window
*/

#include "call_csfml.h"

sfRenderWindow *create_window(void)
{
    sfVideoMode videomode = {1920, 1080, 32};
    sfRenderWindow *window = sfRenderWindow_create(videomode,
        "wolf3d", sfDefaultStyle, NULL);

    return window;
}
