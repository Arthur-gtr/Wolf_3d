/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** anim_ent_shoot
*/

#include "game.h"

void anim_shoot_ss(ennemies_t *ennemi)
{
    ennemi->property->img->rect.top =
        ennemi->property->img->rect.height * 6;
    if (ennemi->property->img->rect.left >=
        ennemi->property->img->rect.width * 2)
        ennemi->property->img->rect.left = 0;
    ennemi->property->img->rect.left +=
        ennemi->property->img->rect.width;
}

void anim_shoot_mutant(ennemies_t *ennemi)
{
    ennemi->property->img->rect.top =
        ennemi->property->img->rect.height * 6;
    if (ennemi->property->img->rect.left >=
        ennemi->property->img->rect.width * 3)
        ennemi->property->img->rect.left = 0;
    if (ennemi->property->img->rect.left ==
        ennemi->property->img->rect.width)
        ennemi->property->img->rect.left +=
        ennemi->property->img->rect.width * 2;
    if (ennemi->property->img->rect.left == 0)
        ennemi->property->img->rect.left +=
            ennemi->property->img->rect.width;
}

void anim_shoot_brut(ennemies_t *ennemi)
{
    ennemi->property->img->rect.top =
        ennemi->property->img->rect.height;
    if (ennemi->property->img->rect.left >=
        ennemi->property->img->rect.width * 2)
        ennemi->property->img->rect.left = 0;
    ennemi->property->img->rect.left +=
        ennemi->property->img->rect.width;
}
