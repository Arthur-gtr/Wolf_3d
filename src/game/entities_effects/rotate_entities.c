/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** run_game
*/

#include "game.h"
#include "ray_casting.h"

void convert_vector_to_deg(entities_t *ent)
{
    ent->angle = (atan2(ent->dir.y, ent->dir.x)) * 180.0f / M_PI;
}

void rotate_right(entities_t *player, float rot_speed)
{
    float old_dir_x = 0;
    float old_plane_x = 0;

    old_dir_x = player->dir.x;
    player->dir.x = player->dir.x * cos(-rot_speed) -
    player->dir.y * sin(-rot_speed);
    player->dir.y = old_dir_x * sin(-rot_speed) + player->dir.y
    * cos(-rot_speed);
    old_plane_x = player->plan.x;
    player->plan.x = player->plan.x * cos(-rot_speed)
    - player->plan.y * sin(-rot_speed);
    player->plan.y = old_plane_x * sin(-rot_speed) + player->plan.y
    * cos(-rot_speed);
    convert_vector_to_deg(player);
}

void rotate_left(entities_t *player, float rot_speed)
{
    float old_dir_x = 0;
    float old_plane_x = 0;

    old_dir_x = player->dir.x;
    player->dir.x = player->dir.x * cos(rot_speed)
    - player->dir.y * sin(rot_speed);
    player->dir.y = old_dir_x * sin(rot_speed) +
    player->dir.y * cos(rot_speed);
    old_plane_x = player->plan.x;
    player->plan.x = player->plan.x * cos(rot_speed)
    - player->plan.y * sin(rot_speed);
    player->plan.y = old_plane_x * sin(rot_speed)
    + player->plan.y * cos(rot_speed);
    convert_vector_to_deg(player);
}

void new_rotate_player(entities_t *player, float rot_speed,
    sfInt32 time)
{
    sfUint8 controller = get_right_stick();

    if (sfKeyboard_isKeyPressed(sfKeyLeft) || controller & LEFT)
        rotate_left(player, rot_speed * time);
    if (sfKeyboard_isKeyPressed(sfKeyRight) || controller & RIGHT)
        rotate_right(player, rot_speed * time);
}
