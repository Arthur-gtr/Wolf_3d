/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** my
*/

#ifndef RAY_CASTING_H
    #define RAY_CASTING_H
    #include <stddef.h>
    #include "call_csfml.h"
    #define CLOSE_DIST 20000.0f
    #define HEIGHT 1080
    #define WIDTH 1920

typedef struct game_handler_s game_handler_t;
typedef struct entities_s entities_t;
typedef struct tab_texture_s tab_texture_t;

typedef struct ray_cast_s {
    /* calcul */
    double camera_x;
    double raydir_x;
    double raydir_y;
    int map_x;
    int map_y;
    double delta_dist_x;
    double delta_dist_y;
    double perp_wall_dist;
    int step_x;
    int step_y;
    double side_dist_x;
    double side_dist_y;
    int hit;
    int side;

    /* texture */
    int texture;
    double wall_x;
    int tex_x;
    sfUint8 *pixels;//POOL de pixel
    sfImage *image;//pool image
    sfTexture *screen_text;
    sfSprite *sprite_screen;

    /* display */
    int height_line;
    int draw_start;
    int draw_end;

    /**/
    double z_buffer[WIDTH];
}ray_cast_t;

/*Ray casting*/
int execute_ray(game_handler_t *game, entities_t *player);
void init_ray_cast(ray_cast_t *ray_cast, entities_t *player, int x);

/*DDA PART*/
void prep_dda(ray_cast_t *ray_cast, entities_t *player);
void execute_dda(ray_cast_t *ray_cast, int map[20][20]);

/*CANCEL FISHEYE*/
void cancel_fisheye(ray_cast_t *ray_cast);

/*Get texture with pixel*/
void det_line(ray_cast_t *ray_cast);
void fill_line(ray_cast_t *ray_cast, int x, tab_texture_t **tab_texture);
void get_text_pixel(ray_cast_t *ray_cast, entities_t *player);

/*Draw buffer how contain screen*/
int draw_wall(ray_cast_t *ray_cast, sfRenderWindow *window);
void convert_vector_to_deg(entities_t *ent);

#endif //RAY_CASTING_H
