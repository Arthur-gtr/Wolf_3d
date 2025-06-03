/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** weapons
*/
#include "call_csfml.h"
#include "game.h"
#include "my.h"
#include "entities.h"

static
void anim_ent_shoot(ennemies_t *shooter)
{
    if (shooter->property->id == ID_SS)
        return anim_shoot_ss(shooter);
    if (shooter->property->id == ID_BRUT)
        return anim_shoot_brut(shooter);
    if (shooter->property->id == ID_MUTANT)
        return anim_shoot_mutant(shooter);
}

static
float calc_dist(player_t *player, ennemies_t *ent, size_t damage)
{
    float new_damage = 0;
    float dist = sqrtf(
        powf((player->property->coord.x - ent->property->coord.x), 2.0) +
        powf((player->property->coord.y - ent->property->coord.y), 2.0));

    if (dist < 0.0)
        dist *= -1.0;
    if (dist == 0)
        dist = 0.1;
    new_damage = damage * (1.0 / dist);
    return new_damage;
}

static
void decrease_life(game_handler_t *g_h, ennemies_t *ent, size_t damage,
    ennemies_t *shooter)
{
    if (shooter != NULL){
        g_h->game->ent->player->property->life -= damage;
        return anim_ent_shoot(shooter);
    }
    if (ent == NULL || ent->property->life <= 0)
        return;
    manage_ennemi_touch(ent, damage, g_h);
}

int knife_shoot(player_t *player, ennemies_t *shooter, game_handler_t *g_h)
{
    ennemies_t *entities_touch = NULL;
    float dist = 0;

    if (shooter == NULL && !launch_p_shoot(player->inventory, 700.0, g_h,
        SO_KNIFE))
        return 0;
    if (shooter == NULL)
        entities_touch = shoot_ray(g_h, player->property);
    if (entities_touch != NULL){
        dist = sqrtf(
            powf((player->property->coord.x -
                entities_touch->property->coord.x), 2.0) +
            powf((player->property->coord.y -
                entities_touch->property->coord.y), 2.0));
        if (dist > 2.0)
            return 0;
    }
    decrease_life(g_h, entities_touch, D_KNIFE, shooter);
    return 0;
}

int gun_shoot(player_t *player, ennemies_t *shooter, game_handler_t *g_h)
{
    ennemies_t *entities_touch = NULL;

    if (shooter == NULL && !launch_p_shoot(player->inventory, 700.0, g_h,
        SO_GUN))
        return 0;
    if (shooter != NULL && !launch_e_shoot(shooter, 700.0, g_h,
        SO_GUN))
        return 0;
    if (shooter == NULL)
        entities_touch = shoot_ray(g_h, player->property);
    decrease_life(g_h, entities_touch, D_GUN, shooter);
    return 0;
}

int shotgun_shoot(player_t *player, ennemies_t *shooter, game_handler_t *g_h)
{
    ennemies_t *entities_touch = NULL;
    float damage = 0;

    if (shooter == NULL && !launch_p_shoot(player->inventory, 1100.0, g_h,
        SO_SHOTGUN))
        return 0;
    if (shooter == NULL)
        entities_touch = shoot_ray(g_h, player->property);
    if (entities_touch != NULL)
        damage = calc_dist(player, entities_touch, D_SHOTGUN);
    decrease_life(g_h, entities_touch, (int)fabs(damage), shooter);
    return 0;
}

int minigun_shoot(player_t *player, ennemies_t *shooter, game_handler_t *g_h)
{
    ennemies_t *entities_touch = NULL;

    if (shooter == NULL && !launch_p_shoot(player->inventory, 100.0, g_h,
        SO_GUN))
        return 0;
    if (shooter != NULL && !launch_e_shoot(shooter, 100.0, g_h,
        SO_GUN))
        return 0;
    if (shooter == NULL)
        entities_touch = shoot_ray(g_h, player->property);
    decrease_life(g_h, entities_touch, D_MINIGUN, shooter);
    return 0;
}

int assault_shoot(player_t *player, ennemies_t *shooter, game_handler_t *g_h)
{
    ennemies_t *entities_touch = NULL;

    if (shooter != NULL && !launch_e_shoot(shooter, 200.0, g_h,
        SO_ASSAULT))
        return 0;
    if (shooter == NULL)
        entities_touch = shoot_ray(g_h, player->property);
    decrease_life(g_h, entities_touch, D_ASSAULT, shooter);
    return 0;
}
