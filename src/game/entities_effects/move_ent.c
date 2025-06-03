/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** move_ent
*/
#include "game.h"
#include "utils.h"

void new_moove_up(entities_t *entities, sfInt32 tim_mili, int map[20][20])
{
    entities->coord.x += (entities->dir.x / 250.0) * tim_mili;
    entities->coord.y += (entities->dir.y / 250.0) * tim_mili;
    if (IS_WALL(map[(int)entities->coord.x][(int)entities->coord.y]) == true){
        entities->coord.x -= (entities->dir.x / 250.0) * tim_mili;
        entities->coord.y -= (entities->dir.y / 250.0) * tim_mili;
    }
}

void new_moove_down(entities_t *entities, sfInt32 tim_mili, int map[20][20])
{
    entities->coord.x -= (entities->dir.x / 250.0) * tim_mili;
    entities->coord.y -= (entities->dir.y / 250.0) * tim_mili;
    if (IS_WALL(map[(int)entities->coord.x][(int)entities->coord.y]) == true){
        entities->coord.x += (entities->dir.x / 250.0) * tim_mili;
        entities->coord.y += (entities->dir.y / 250.0) * tim_mili;
    }
}

void new_moove_right(entities_t *entities, sfInt32 tim_mili, int map[20][20])
{
    entities->coord.x += (entities->dir.y / 250.0) * tim_mili;
    entities->coord.y += (-entities->dir.x / 250.0) * tim_mili;
    if (IS_WALL(map[(int)entities->coord.x][(int)entities->coord.y]) == true){
        entities->coord.x -= (entities->dir.y / 250.0) * tim_mili;
        entities->coord.y -= (-entities->dir.x / 250.0) * tim_mili;
    }
}

void new_moove_left(entities_t *entities, sfInt32 tim_mili, int map[20][20])
{
    entities->coord.x -= (entities->dir.y / 250.0) * tim_mili;
    entities->coord.y -= (-entities->dir.x / 250.0) * tim_mili;
    if (IS_WALL(map[(int)entities->coord.x][(int)entities->coord.y]) == true){
        entities->coord.x += (entities->dir.y / 250.0) * tim_mili;
        entities->coord.y += (-entities->dir.x / 250.0) * tim_mili;
    }
}
