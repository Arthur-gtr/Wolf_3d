/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** animation_weapons
*/

#include "game.h"

void animate_gun(game_handler_t *g_h, gun_t *gun)
{
    sfTime time = sfClock_getElapsedTime(g_h->game->hud->animation);
    float second = time.microseconds / 1000.0;

    if (second > 700.0 / 6.0) {
        if (gun->img->rect.left <= 256)
            gun->img->rect.left += 65;
        if (gun->img->rect.left > 256){
            gun->img->rect.left = 1;
            g_h->game->hud->anim = false;
        }
        sfSprite_setTextureRect(gun->img->sprite, gun->img->rect);
        sfClock_restart(g_h->game->hud->animation);
    }
}

void animate_shgun(game_handler_t *g_h, gun_t *shotgun)
{
    sfTime time = sfClock_getElapsedTime(g_h->game->hud->animation);
    float second = time.microseconds / 1000.0;

    if (second > 1000.0 / 6.0) {
        if (shotgun->img->rect.left == shotgun->img->rect.width * 2
            && shotgun->img->rect.top == shotgun->img->rect.height) {
            g_h->game->hud->anim = false;
            shotgun->img->rect = (sfIntRect){0, 0, 466, 412};
        }
        if (shotgun->img->rect.left == shotgun->img->rect.width * 2 &&
            shotgun->img->rect.top == 0) {
            shotgun->img->rect.left = 0;
            shotgun->img->rect.top = shotgun->img->rect.height;
        }
        if (shotgun->img->rect.left < shotgun->img->rect.width * 2
            && g_h->game->hud->anim)
            shotgun->img->rect.left += shotgun->img->rect.width;
        sfSprite_setTextureRect(shotgun->img->sprite, shotgun->img->rect);
        sfClock_restart(g_h->game->hud->animation);
    }
}

void animate_minigun(game_handler_t *g_h, gun_t *gun)
{
    sfTime time = sfClock_getElapsedTime(g_h->game->hud->animation);
    float second = time.microseconds / 1000.0;

    if (second > 100.0 / 2.0) {
        if ((!g_h->game->ent->player->is_shooting || gun->magazine <= 0) &&
            gun->img->rect.left == gun->img->rect.width * 3)
            g_h->game->hud->anim = false;
        if (gun->img->rect.left == gun->img->rect.width * 3)
            gun->img->rect.left = gun->img->rect.width;
        if (gun->img->rect.left < gun->img->rect.width * 3
            && g_h->game->hud->anim)
            gun->img->rect.left += gun->img->rect.width;
        sfSprite_setTextureRect(gun->img->sprite, gun->img->rect);
        sfClock_restart(g_h->game->hud->animation);
    }
}
