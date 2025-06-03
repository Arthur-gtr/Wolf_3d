/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_weapons
*/

#include "game.h"
#include "string.h"

gun_t *init_knife(game_handler_t *g_h)
{
    gun_t *knife = malloc(sizeof(gun_t));

    knife->img = set_img(T_3D_KNIFE, (sfIntRect){1, 0, 64, 64},
        (sfVector2f){630, 950}, g_h);
    sfSprite_setOrigin(knife->img->sprite, (sfVector2f){0,
        knife->img->rect.height});
    sfSprite_setScale(knife->img->sprite, (sfVector2f){10, 10});
    knife->ammo = 0;
    knife->mag_cap = 0;
    knife->magazine = knife->mag_cap;
    knife->shoot_so = get_sound(g_h->sound, SO_KNIFE);
    knife->gun_shot = &knife_shoot;
    return knife;
}

gun_t *init_gun(game_handler_t *g_h)
{
    gun_t *gun = malloc(sizeof(gun_t));

    if (gun == NULL)
        return NULL;
    gun->img = set_img(T_3D_GUN, (sfIntRect){1, 0, 64, 64},
        (sfVector2f){690, 950}, g_h);
    sfSprite_setOrigin(gun->img->sprite, (sfVector2f){0,
        gun->img->rect.height});
    sfSprite_setScale(gun->img->sprite, (sfVector2f){10, 10});
    gun->save_file = strdup("gun_ammo.bin");
    if (gun->save_file == NULL || gun->img == NULL)
        return NULL;
    if (g_h->game->have_been_f || !load_from_file(g_h, gun->save_file,
        &gun->ammo, sizeof(gun->ammo)))
        gun->ammo = 60;
    gun->mag_cap = 8;
    gun->magazine = gun->mag_cap;
    gun->shoot_so = get_sound(g_h->sound, SO_GUN);
    gun->gun_shot = &gun_shoot;
    return gun;
}

gun_t *init_shotgun(game_handler_t *g_h)
{
    gun_t *shotgun = malloc(sizeof(gun_t));

    if (shotgun == NULL)
        return NULL;
    shotgun->img = set_img(T_3D_SHOTGUN, (sfIntRect){0, 0, 466, 412},
        (sfVector2f){990, 950}, g_h);
    sfSprite_setOrigin(shotgun->img->sprite, (sfVector2f){0,
        shotgun->img->rect.height});
    sfSprite_setScale(shotgun->img->sprite, (sfVector2f){1, 1});
    shotgun->save_file = strdup("shotgun_ammo.bin");
    if (shotgun->save_file == NULL || shotgun->img == NULL)
        return NULL;
    if (g_h->game->have_been_f || !load_from_file(g_h, shotgun->save_file,
        &shotgun->ammo, sizeof(shotgun->ammo)))
        shotgun->ammo = 20;
    shotgun->mag_cap = 5;
    shotgun->magazine = shotgun->mag_cap;
    shotgun->shoot_so = get_sound(g_h->sound, SO_SHOTGUN);
    shotgun->gun_shot = &shotgun_shoot;
    return shotgun;
}

gun_t *init_minigun(game_handler_t *g_h)
{
    gun_t *minigun = malloc(sizeof(gun_t));

    if (minigun == NULL)
        return NULL;
    minigun->img = set_img(T_3D_MINIGUN, (sfIntRect){80, 0, 80, 75},
        (sfVector2f){825, 950}, g_h);
    sfSprite_setOrigin(minigun->img->sprite, (sfVector2f){0,
        minigun->img->rect.height});
    sfSprite_setScale(minigun->img->sprite, (sfVector2f){5, 5});
    minigun->save_file = strdup("minigun_ammo.bin");
    if (minigun->save_file == NULL || minigun->img == NULL)
        return NULL;
    if (g_h->game->have_been_f || !load_from_file(g_h, minigun->save_file,
        &minigun->ammo, sizeof(minigun->ammo)))
        minigun->ammo = 200;
    minigun->mag_cap = 100;
    minigun->magazine = minigun->mag_cap;
    minigun->shoot_so = get_sound(g_h->sound, SO_SHOTGUN);
    minigun->gun_shot = &minigun_shoot;
    return minigun;
}

gun_t **init_weapons(game_handler_t *g_h)
{
    gun_t **guns = malloc(sizeof(gun_t *) * NB_GUN);

    if (guns == NULL)
        return NULL;
    guns[W_ID_KNIFE] = init_knife(g_h);
    guns[W_ID_GUN] = init_gun(g_h);
    guns[W_ID_SHOTGUN] = init_shotgun(g_h);
    guns[W_ID_MINIGUN] = init_minigun(g_h);
    return guns;
}
