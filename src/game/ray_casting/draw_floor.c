/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** draw_floor
*/

#include "game.h"

static
void find_ray_dir(entities_t *player, floor_ceiling_t *drawable_zone)
{
    drawable_zone->ray_dir_0.x = player->dir.x - player->plan.x;
    drawable_zone->ray_dir_0.y = player->dir.y - player->plan.y;
    drawable_zone->ray_dir_1.x = player->dir.x + player->plan.x;
    drawable_zone->ray_dir_1.y = player->dir.y + player->plan.y;
}

static
int fill_floor(entities_t *player, floor_ceiling_t *drawable_zone, int y)
{
    drawable_zone->p = y - HEIGHT / 2;
    if (drawable_zone->p == 0)
        return 1;
    drawable_zone->pos_z = 0.5f * HEIGHT;
    drawable_zone->row_dist = drawable_zone->pos_z / drawable_zone->p;
    drawable_zone->floor_step.x = drawable_zone->row_dist *
        (drawable_zone->ray_dir_1.x - drawable_zone->ray_dir_0.x) / WIDTH;
    drawable_zone->floor_step.y = drawable_zone->row_dist *
        (drawable_zone->ray_dir_1.y - drawable_zone->ray_dir_0.y) / WIDTH;
    drawable_zone->floor.x = player->coord.x +
        drawable_zone->row_dist * drawable_zone->ray_dir_0.x;
    drawable_zone->floor.y = player->coord.y +
        drawable_zone->row_dist * drawable_zone->ray_dir_0.y;
    return 0;
}

void init_texture_px(floor_ceiling_t *drawable_zone,
    tab_texture_t **tab_texture)
{
    drawable_zone->cell.x = (int)(drawable_zone->floor.x);
    drawable_zone->cell.y = (int)(drawable_zone->floor.y);
    drawable_zone->tex.x = (int)(64 * (drawable_zone->floor.x
        - drawable_zone->cell.x)) & (64 - 1);
    drawable_zone->tex.y = (int)(64 * (drawable_zone->floor.y
        - drawable_zone->cell.y)) & (64 - 1);
    drawable_zone->color = sfImage_getPixel(tab_texture[FLOOR]->img,
        drawable_zone->tex.x, drawable_zone->tex.y);
}

void draw_floor(entities_t *player, ray_cast_t *ray_cast,
    tab_texture_t **tab_texture)
{
    floor_ceiling_t drawable_zone = {0};

    find_ray_dir(player, &drawable_zone);
    for (int y = HEIGHT / 2 + 1; y < HEIGHT; y++) {
        if (fill_floor(player, &drawable_zone, y))
            continue;
        for (int x = 0; x < WIDTH; x++) {
            init_texture_px(&drawable_zone, tab_texture);
            put_color_in_buffer(ray_cast->pixels, drawable_zone.color,
                (y * WIDTH + x) * 4, y);
            drawable_zone.color = sfImage_getPixel(tab_texture[CEILING]->img,
                drawable_zone.tex.x, drawable_zone.tex.y);
            put_color_in_buffer(ray_cast->pixels, drawable_zone.color,
                (((HEIGHT - y - 1) * WIDTH + x) * 4), y);
            drawable_zone.floor.x += drawable_zone.floor_step.x;
            drawable_zone.floor.y += drawable_zone.floor_step.y;
        }
    }
}
