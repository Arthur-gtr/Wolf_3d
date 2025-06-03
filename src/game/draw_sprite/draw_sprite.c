/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** draw_sprite
*/

#include "game.h"
#include "in_game.h"
#include "ray_casting.h"
#include <string.h>

/*
effectue plusieur calul pour déterminer la position
de l' entité par rapport a la position du joueur
renvoie true si l' ennemie est dans la zone vu par le plan
camera determiner pas la vecteur direction du joueur
*/
bool fill_draw_ent(draw_sprite_t *draw_ent, entities_t *entities,
    entities_t *player)
{
    double det = 0;

    draw_ent->sprite_coord.x = entities->coord.x - player->coord.x;
    draw_ent->sprite_coord.y = entities->coord.y - player->coord.y;
    det = (player->plan.x * player->dir.y - player->dir.x * player->plan.y);
    if (det == 0)
        return false;
    draw_ent->inv_mat = 1.0f / det;
    draw_ent->transform.x = draw_ent->inv_mat *
        (player->dir.y * draw_ent->sprite_coord.x -
        player->dir.x * draw_ent->sprite_coord.y);
    draw_ent->transform.y = draw_ent->inv_mat *
        (-player->plan.y * draw_ent->sprite_coord.x +
        player->plan.x * draw_ent->sprite_coord.y);
    draw_ent->sprite_screen_x = (int)((WIDTH / 2) *
        (1 + draw_ent->transform.x / draw_ent->transform.y));
    if (draw_ent->transform.y > 0)
            return true;
    return false;
}

void get_size_ent(draw_sprite_t *draw_ent)
{
    int sprite_width = 0;
    int sprite_height = abs((int)(HEIGHT / (draw_ent->transform.y)));

    draw_ent->draw_start.y = -sprite_height / 2 + HEIGHT / 2;
    if (draw_ent->draw_start.y < 0)
        draw_ent->draw_start.y = 0;
    draw_ent->draw_end.y = sprite_height / 2 + HEIGHT / 2;
    if (draw_ent->draw_end.y >= HEIGHT)
        draw_ent->draw_end.y = HEIGHT - 1;
    sprite_width = abs((int)(HEIGHT / (draw_ent->transform.y)));
    draw_ent->draw_start.x = -sprite_width / 2 + draw_ent->sprite_screen_x;
    if (draw_ent->draw_start.x < 0)
        draw_ent->draw_start.x = 0;
    draw_ent->draw_end.x = sprite_width / 2 + draw_ent->sprite_screen_x;
    if (draw_ent->draw_end.x >= WIDTH)
        draw_ent->draw_end.x = WIDTH - 1;
    draw_ent->sprite_width = sprite_width;
    draw_ent->sprite_height = sprite_height;
}

/*
simulation de float avec
virgule fix 8 bit
*/
void fill_ent_yray(entities_t *entities, draw_sprite_t *draw_ent,
    ray_cast_t *ray_cast, int x)
{
    int texture_pos_y_scaled = 0;
    int tex_y = 0;
    sfColor pixel = {0};
    int index = 0;

    for (int y = draw_ent->draw_start.y; y < draw_ent->draw_end.y; y++){
        texture_pos_y_scaled = y * 256 - HEIGHT * 128 +
            draw_ent->sprite_height * 128;
        tex_y = ((texture_pos_y_scaled * 64) / draw_ent->sprite_height) / 256;
        tex_y = (tex_y > 63) ? 63 : tex_y;
        tex_y = (tex_y < 0) ? 0 : tex_y;
        draw_ent->tex_x = (draw_ent->tex_x > 63) ? 63 : draw_ent->tex_x;
        draw_ent->tex_x = (draw_ent->tex_x < 0) ? 0 : draw_ent->tex_x;
        pixel = sfImage_getPixel(entities->img->img, draw_ent->tex_x +
            entities->img->rect.left, tex_y + entities->img->rect.top);
        index = (y * 1920 + x) * 4;
        put_color_in_buffer(ray_cast->pixels, pixel, index,
            ray_cast->height_line);
    }
}

void draw_one_ent(entities_t *entities, draw_sprite_t *draw_ent,
    ray_cast_t *ray_cast)
{
    draw_ent->tex_x = 0;
    get_size_ent(draw_ent);
    for (int line = draw_ent->draw_start.x; line < draw_ent->draw_end.x;
        line++){
        if (draw_ent->sprite_width == 0 || draw_ent->sprite_height == 0)
            continue;
        draw_ent->tex_x = (int)(256 * (line - (-draw_ent->sprite_width / 2 +
            draw_ent->sprite_screen_x)) * 64 / draw_ent->sprite_width) / 256;
        if (draw_ent->transform.y > 0 && line > 0 && line < WIDTH &&
            draw_ent->transform.y < ray_cast->z_buffer[line])
            fill_ent_yray(entities, draw_ent, ray_cast, line);
    }
}

/*
Parcour recursife de la liste chainé
en commencant par la head et en suivant les nexts
-----
draw sprite me permet d' effectuer tous les calcul
*/
static void draw_lkd_sprite(node_t *node, entities_t *player,
    sfRenderWindow *window, ray_cast_t *ray_cast)
{
    entities_t *entitie = NULL;
    draw_sprite_t draw_ent = {0};

    memset(ray_cast->pixels, 0, 1920 * 1080 * 4);
    if (node == NULL)
        return;
    entitie = (entities_t *)node->data;
    if (fill_draw_ent(&draw_ent, entitie, player) == false)
        return draw_lkd_sprite(node->next, player, window, ray_cast);
    draw_one_ent(entitie, &draw_ent, ray_cast);
    draw_wall(ray_cast, window);
    return draw_lkd_sprite(node->next, player, window, ray_cast);
}

/*permet d' afficher tous les sprite
en effectuant la fonction de sort par
rapport a la distance sans sqrt
puis lance une fonction recursive
qui calcul si on peut draw le sprite et le display.*/
void draw_sprite(game_handler_t *game, sfRenderWindow *window)
{
    node_t *node = (node_t *)game->game->ent->entities->head;
    entities_t *player = game->game->ent->player->property;

    draw_lkd_sprite(node, player, window, &game->ray_cast);
    return;
}
