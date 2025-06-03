/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** handle_ent_event
*/
#include "game.h"

const angle_sprite_t SPRITE_TAB[] = {
    {{337.5, 22.5}, 0},
    {{22.5, 67.5}, 1},
    {{67.5, 112.5}, 2},
    {{112.5, 157.5}, 3},
    {{157.5, 202.5}, 4},
    {{202.5, 247.5}, 5},
    {{247.5, 292.5}, 6},
    {{292.5, 337.5}, 7}
};


static
void aim_player(player_t *player, ennemies_t *ennemies)
{
    sfVector2f dir = { player->property->coord.x - ennemies->property->coord.x,
        player->property->coord.y - ennemies->property->coord.y};
    float length = sqrtf(dir.x * dir.x + dir.y * dir.y);

    if (length == 0){
        ennemies->property->dir = (sfVector2f){0.0, 0.0};
        return;
    }
    ennemies->property->dir = (sfVector2f){dir.x / length, dir.y / length};
    convert_vector_to_deg(ennemies->property);
    return;
}

float get_relative_angle(entities_t *player, entities_t *ennemies)
{
    sfVector2f position_v = {player->coord.x - ennemies->coord.x,
        player->coord.y - ennemies->coord.y};
    double rad_angle = ennemies->angle * (M_PI / 180.0);
    sfVector2f angle_v = {cosf(rad_angle), sinf(rad_angle)};
    float scalaire = 0;
    float cross = 0;
    float magA = sqrtf(position_v.x * position_v.x +
        position_v.y * position_v.y);
    float angledeg = 0;

    if (magA == 0)
        return 0;
    scalaire = angle_v.x * position_v.x + angle_v.y * position_v.y;
    cross = angle_v.x * position_v.y - angle_v.y * position_v.x;
    angledeg = atan2f(cross, scalaire) * (180.0 / M_PI);
    if (angledeg < 0)
        return angledeg + 360.0;
    return angledeg;
}

void rotate_sprite(player_t *player, ennemies_t *ennemi)
{
    float angle;

    convert_vector_to_deg(ennemi->property);
    if (ennemi->property->id == ID_BRUT)
        return;
    angle = get_relative_angle(player->property, ennemi->property);
    if (angle > SPRITE_TAB[0].angle_interval.x ||
        angle < SPRITE_TAB[0].angle_interval.y)
        ennemi->property->img->rect.left = 0;
    for (int i = 1; i < 8; i++)
        if (angle > SPRITE_TAB[i].angle_interval.x &&
            angle < SPRITE_TAB[i].angle_interval.y)
            ennemi->property->img->rect.left = 65 * SPRITE_TAB[i].sprite_coef;
    sfSprite_setTextureRect(ennemi->property->img->sprite,
        ennemi->property->img->rect);
}

static
bool death_choice(node_t *actual, int width_max, game_handler_t *g_h)
{
    ennemies_t *ennemie = (ennemies_t *)actual->data;

    if (ennemie->property->img->rect.left >=
        ennemie->property->img->rect.width * width_max)
        destroy_nodes(g_h->game->ent->ennemies, actual);
    if (ennemie->property->img->rect.left <
        ennemie->property->img->rect.width * width_max){
        ennemie->property->img->rect.left +=
            ennemie->property->img->rect.width;
        sfClock_restart(ennemie->clock_touch.clock);
    }
    return false;
}

static
bool death_anim(node_t *actual, game_handler_t *g_h)
{
    ennemies_t *ennemie = (ennemies_t *)actual->data;

    if (ennemie->property->life <= 0){
        if (ennemie->clock_touch.time.microseconds / 1000.0 < 250.0)
            return false;
        if (ennemie->property->id == ID_SS)
            return death_choice(actual, 5, g_h);
        if (ennemie->property->id == ID_MUTANT)
            return death_choice(actual, 6, g_h);
        if (ennemie->property->id == ID_BRUT)
            return death_choice(actual, 3, g_h);
        return false;
    }
    return true;
}

static
bool restart_anim(node_t *actual, game_handler_t *g_h)
{
    ennemies_t *ennemie = (ennemies_t *)actual->data;

    if (ennemie->property->id == ID_BRUT || ennemie->is_shooting)
        aim_player(g_h->game->ent->player, ennemie);
    ennemie->clock_touch.time =
        sfClock_getElapsedTime(ennemie->clock_touch.clock);
    if (!death_anim(actual, g_h))
        return false;
    if (ennemie->clock_touch.time.microseconds / 1000.0 < 200.0)
        return false;
    return true;
}

static
void detect_player(ennemies_t *ent, game_handler_t *game_handler)
{
    if (sfClock_getElapsedTime(ent->clock_search.clock).microseconds / 1000.0
        > 500.0){
        ent->last_frame_shooting = ent->is_shooting;
        ent->is_shooting = search_player(game_handler,
            ent->property);
        sfClock_restart(ent->clock_search.clock);
    }
    if (ent->is_shooting == false && ent->last_frame_shooting == true){
        ent->anim = 0;
        ent->property->img->rect.left = 0;
        ent->property->img->rect.top = 0;
        sfClock_restart(ent->property->clock.clock);
    }
}

//actual node set at the second node because the first is the player
void handle_ent_event(game_handler_t *game_handler, entities_handler_t *ent)
{
    node_t *actual = ent->ennemies->head;
    node_t *next = NULL;
    player_t *player = ent->player;

    for (; actual; actual = next){
        next = actual->next;
        if (!restart_anim(actual, game_handler))
            continue;
        detect_player(actual->data, game_handler);
        if (((ennemies_t *)actual->data)->is_shooting){
            ((ennemies_t *)actual->data)->
                gun_shot(player, actual->data, game_handler);
            continue;
        }
        move_ennemies(actual->data, game_handler);
        rotate_sprite(player, actual->data);
    }
}
