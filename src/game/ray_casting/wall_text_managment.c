/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** wall_text__managment
*/
#include "ray_casting.h"
#include "game.h"

void det_line(ray_cast_t *ray_cast)
{
    int lineHeight = (int)(HEIGHT / ray_cast->perp_wall_dist);
    int drawStart = -lineHeight / 2 + HEIGHT / 2;
    int drawEnd = lineHeight / 2 + HEIGHT / 2;

    ray_cast->height_line = lineHeight;
    ray_cast->draw_start = (drawStart < 0) ? 0 : drawStart;
    ray_cast->draw_end = (drawEnd >= HEIGHT) ? HEIGHT - 1 : drawEnd;
}

/*
** get coord of the pixel in the picture
** ensuite on peut fil le buffer[][] avec x
** la boucle principale
*/
void get_text_pixel(ray_cast_t *ray_cast, entities_t *player)
{
    ray_cast->wall_x = (ray_cast->side == 0)
        ? player->coord.y + ray_cast->perp_wall_dist * ray_cast->raydir_y
        : player->coord.x + ray_cast->perp_wall_dist * ray_cast->raydir_x;
    ray_cast->wall_x -= floor((ray_cast->wall_x));
    ray_cast->tex_x = (int)(ray_cast->wall_x * (double)(64));
}

sfColor get_shadow(int distance, sfColor pixel)
{
    double shade = distance / 540.0f;
    sfColor color = {0};

    if (pixel.a == 0)
        return pixel;
    if (shade > 1)
        shade = 1;
    if (shade < 0.25)
        shade = 0.25;
    color = (sfColor){
        .r = (sfUint8)(pixel.r * shade),
        .g = (sfUint8)(pixel.g * shade),
        .b = (sfUint8)(pixel.b * shade),
        .a = 255};
    return color;
}

/*
** prend un sfcolor et le place dans un buffer aplatie 1D
*/
void put_color_in_buffer(sfUint8 *array_pixel,
    sfColor new_pixel, int index_storage, int dist)
{
    new_pixel = get_shadow(dist, new_pixel);
    array_pixel[index_storage] = new_pixel.r;
    array_pixel[index_storage + 1] = new_pixel.g;
    array_pixel[index_storage + 2] = new_pixel.b;
    array_pixel[index_storage + 3] = new_pixel.a;
}

void fill_line(ray_cast_t *ray_cast, int x, tab_texture_t **tab_texture)
{
    sfColor pixel_to_add = {0, 0, 0, 0};
    double step = 1.0 * 64 /
        ray_cast->height_line;
    double tex_pos = (ray_cast->draw_start - HEIGHT /
        2 + ray_cast->height_line / 2) * step;
    int tex_y = 0;
    int index = 0;

    for (int y = ray_cast->draw_start; y < ray_cast->draw_end; y++) {
        tex_y = (int)tex_pos % 64;
        ray_cast->tex_x = ray_cast->tex_x % 64;
        tex_pos += step;
        pixel_to_add =
            sfImage_getPixel(tab_texture[ray_cast->texture - 1]->img,
            ray_cast->tex_x, tex_y);
        index = (y * 1920 + x) * 4;
        put_color_in_buffer(ray_cast->pixels, pixel_to_add,
            index, ray_cast->height_line);
    }
}
