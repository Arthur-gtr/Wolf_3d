/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** launch_ray
*/
#include "game.h"

bool is_between_point(entities_t *entity,
    entities_t *player, sfVector2f end_point, float error)
{
    float dx1 = end_point.x - player->coord.x;
    float dy1 = end_point.y - player->coord.y;
    float dx2 = entity->coord.x - player->coord.x;
    float dy2 = entity->coord.y - player->coord.y;
    float cross = dx1 * dy2 - dy1 * dx2;
    float dot = 0;
    float len_sq = 0;

    if (cross > error)
        return false;
    dot = dx2 * dx1 + dy2 * dy1;
    if (dot < 0)
        return false;
    len_sq = dx1 * dx1 + dy1 * dy1;
    if (dot > len_sq)
        return false;
    return true;
}

/*
on fait une recursion sur node next
on garde toujours player_co car elle ne change jamais
wall_co correspond a la coord
on récupere les coords de l' entité dans la node
*/
static
bool find_the_closer(entities_t *ent,
    entities_t *player_ent, sfVector2f wall_co)
{
    if (ent == NULL)
        return false;
    if (is_between_point(player_ent, ent, wall_co, 1.0) == true)
        return true;
    return false;
}

bool search_player(game_handler_t *game, entities_t *ennemie)
{
    int x = WIDTH / 2 + 50;

    init_ray_cast(&game->ray_cast, ennemie, x);
    prep_dda(&game->ray_cast, ennemie);
    execute_dda(&game->ray_cast,
        game->game->level.map[game->game->level.actual_level]);
    return find_the_closer(ennemie,
        game->game->ent->player->property,
        (sfVector2f){(float)game->ray_cast.map_x,
        (float)game->ray_cast.map_y});
}

static
ennemies_t *find_the_closer_en(node_t *node,
    entities_t *player_ent, sfVector2f wall_co)
{
    ennemies_t *ennemi = NULL;

    if (node == NULL)
        return NULL;
    ennemi = (ennemies_t *)node->data;
    if (ennemi->property->life > 0 &&
        is_between_point(ennemi->property, player_ent, wall_co, 1.0) == true)
        return ennemi;
    return find_the_closer_en(node->next, player_ent, wall_co);
}

ennemies_t *shoot_ray(game_handler_t *game, entities_t *player)
{
    int x = WIDTH / 3;

    init_ray_cast(&game->ray_cast, game->game->ent->player->property, x);
    prep_dda(&game->ray_cast, player);
    execute_dda(&game->ray_cast,
        game->game->level.map[game->game->level.actual_level]);
    return find_the_closer_en(game->game->ent->ennemies->head,
        player, (sfVector2f){(float)game->ray_cast.map_x,
        (float)game->ray_cast.map_y});
}
