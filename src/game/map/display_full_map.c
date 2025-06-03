/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** display_full_map
*/
#include "game.h"
#include "call_csfml.h"
#include <stdbool.h>
#include "entities.h"

/*
** convert the map
** to the map in memory
**
*/
sfVector2f get_coord(sfVector2f coord_window)
{
    coord_window.x -= (960 - ((60 * MAP_WIDTH) / 2));
    coord_window.y -= (520 - ((60 * MAP_HEIGHT) / 2));
    return (sfVector2f)
        {.x = (coord_window.x / 60),
        .y = (coord_window.y / 60)};
}

bool is_in_real_wall(sfVector2f coord)
{
    coord.x -= (960 - ((60 * MAP_WIDTH) / 2));
    coord.y -= (520 - ((60 * MAP_HEIGHT) / 2));
    if ((int)(coord.x) / 60 >= MAP_WIDTH || (int)(coord.y) / 60 >= MAP_HEIGHT)
        return true;
    if (is_wall((int)(coord.y) / 60, (int)(coord.x) / 60) == true)
        return true;
    return false;
}

static
void display_2dplayer(game_handler_t *game_handler)
{
    move_player(&game_handler->entities.player.property);
    rotate_player(&game_handler->entities.player.property);
    sfRenderWindow_drawSprite(game_handler->window,
        game_handler->entities.player.property.sprite, NULL);
    sfSprite_setPosition(game_handler->entities.player.property.sprite,
        game_handler->entities.player.property.coord);
}

/*
parcour le int **
et dessine un mur
si il y a un mur
*/
static
void display_one_2dwall(entities_t *wall, sfRenderWindow *window, int y)
{
    for (int x = 0; x < MAP_WIDTH; x++)
        if (is_wall(y, x) == true){
            sfSprite_setPosition(wall->sprite,
            (sfVector2f){((960 - ((60 * MAP_WIDTH) / 2)) + (x * 60)),
                        ((520 - ((60 * MAP_HEIGHT) / 2)) + (y * 60))});
            sfRenderWindow_drawSprite(window, wall->sprite, NULL);
        }
}

static
void display_2dwalls(entities_t *wall, sfRenderWindow *window)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
        display_one_2dwall(wall, window, y);
}

static
sfVector2f dichotomie(entities_t *property,
    float angle_option, double precision)
{
    sfVector2f tmp_coord;
    sfVector2f coord = property->coord;

    while (is_in_real_wall(coord) == false){
        tmp_coord = (sfVector2f){(sin(DEG_TO_RAD(-1 * (property->angle +
            angle_option))))
        * (precision), cos(DEG_TO_RAD(-1 * (property->angle + angle_option))) *
        (precision)};
        coord = (sfVector2f){coord.x + tmp_coord.x, coord.y + tmp_coord.y};
    }
    coord = (sfVector2f){coord.x - tmp_coord.x, coord.y - tmp_coord.y};
    return coord;
}

static
void display_ray_casting(entities_t *entities, sfRenderWindow *window,
    float angle_option, int precision)
{
    sfVertexArray* line = sfVertexArray_create();
    sfVector2f coord = entities->coord;
    sfVertex p1 = {coord, (check_l2() == true) ? sfRed : sfGreen, {0, 0}};
    sfVertex p2 = {coord, (check_l2() == true) ? sfRed : sfGreen, {0, 0}};

    for (double i = precision; i > 1; i = i / 2)
        coord = dichotomie(entities, angle_option, i);
    p2 = (sfVertex){coord, (check_l2() == true) ? sfRed : sfGreen, {0, 0}};
    sfVertexArray_setPrimitiveType(line, sfLines);
    sfVertexArray_append(line, p1);
    sfVertexArray_append(line, p2);
    sfRenderWindow_drawVertexArray(window, line, NULL);
    sfVertexArray_destroy(line);
}

/*
** RAY CASTING
** SI ON VEUT FAIRE
** UN NIVEAU DE GRAPHISME
** FAUT CHANGER precision
**
*/
float get_coord_wall(entities_t *entities, float angle, int precision)
{
    sfVector2f coord_player = entities->coord;
    sfVector2f coord_wall = entities->coord;
    sfVector2f player_in_map = {0, 0};
    sfVector2f wall_in_map = {0, 0};
    float dist = 0;

    for (double i = precision; i > 0.25; i = i * 0.5)
        coord_wall = dichotomie(entities, angle, i);
    player_in_map = get_coord(coord_player);
    wall_in_map = get_coord(coord_wall);
    dist = sqrt(((player_in_map.x - wall_in_map.x) *
    (player_in_map.x - wall_in_map.x))
    + ((player_in_map.y - wall_in_map.y)
    * (player_in_map.y - wall_in_map.y)));
    return dist;
}

int display_full_map(game_handler_t *game_handler)
{
    sfRenderWindow_clear(game_handler->screen->win, sfBlack);
    display_2dplayer(game_handler);
    display_2dwalls(game_handler->game->ent.player->property,
        game_handler->screen->win);
    for (float i = -45; i < 45; i += 1){
        display_ray_casting(game_handler->game->ent.player->property,
        game_handler->win, i, 60);
    }
    check_back_to_menu(game_handler);
    return 0;
}
