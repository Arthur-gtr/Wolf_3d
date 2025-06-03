/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** utils
*/

#ifndef INCLUDED_UTILS_H
    #define INCLUDED_UTILS_H
    #include "call_csfml.h"
    #include <stdbool.h>
    #define NB_WALL 4
    #define IS_WALL(x) ( x > 0 && x < NB_WALL) ? true : false
    #define WALL_IRON 1
    #define WALL_FLAG_ARCH WALL_IRON + 1
    #define WALL_BRICK WALL_FLAG_ARCH + 1
    #define WALL_BRICK2 WALL_BRICK + 1
    #define T_BRUT WALL_BRICK2 + 1
    #define T_MUTANT T_BRUT + 1
    #define T_SS T_MUTANT + 1
    #define T_M_BG T_SS + 1
    #define T_M2D T_M_BG + 1
    #define T_M3D T_M2D + 1
    #define T_P_2D T_M3D + 1
    #define T_B_S1 T_P_2D + 1
    #define T_B_S2 T_B_S1 + 1
    #define T_B_S3 T_B_S2 + 1
    #define T_B_EXIT T_B_S3 + 1
    #define T_B_SETTINGS T_B_EXIT + 1
    #define T_B_BACK T_B_SETTINGS + 1
    #define T_ARR_L T_B_BACK + 1
    #define T_ARR_R T_ARR_L + 1
    #define T_B_HOME T_ARR_R + 1
    #define T_3D_KNIFE T_B_HOME + 1
    #define T_3D_GUN T_3D_KNIFE + 1
    #define T_3D_SHOTGUN T_3D_GUN + 1
    #define T_3D_MINIGUN T_3D_SHOTGUN + 1
    #define T_2D_KNIFE T_3D_MINIGUN + 1
    #define T_2D_GUN T_2D_KNIFE + 1
    #define T_2D_SHOTGUN T_2D_GUN + 1
    #define T_2D_MINIGUN T_2D_SHOTGUN + 1
    #define T_HUD T_2D_MINIGUN + 1
    #define T_AMMO T_HUD +1
    #define T_LIFE T_AMMO +1

    #define SO_B_MOVE 0
    #define SO_B_CLICK 1
    #define SO_B_P_STEP 2
    #define SO_KNIFE 3
    #define SO_GUN 4
    #define SO_SHOTGUN 5
    #define SO_MINIGUN 6
    #define SO_DIYING 7
    #define SO_ASSAULT 8
    #define SO_OBJ 9

typedef struct game_handler_s game_handler_t;

typedef struct img_s {
    sfVector2f pos;
    sfIntRect rect;
    sfTexture *texture;
    sfSprite *sprite;
    size_t texture_id;
    sfImage *img;
} img_t;

typedef struct tab_texture_s {
    sfTexture *texture;
    sfImage *img;
    size_t id;
    char *file;
} tab_texture_t;

typedef struct tab_sound_s {
    sfSound *sound;
    sfSoundBuffer *buffer;
    size_t id;
    char *file;
} tab_sound_t;

img_t *set_img(size_t texture_token, sfIntRect rect, sfVector2f pos,
    game_handler_t *g_h);
sfText *set_txt(size_t size, sfColor color, sfVector2f position, char *str);
sfTexture *get_texture(tab_texture_t **tab, size_t token);
sfSound *get_sound(tab_sound_t **tab, size_t token);
bool load_from_file(game_handler_t *g_h, char *file, void *to_rd, ssize_t sz);
bool save_to_file(game_handler_t *g_h, char *file, void *to_rd, ssize_t sz);
void free_game_handler(game_handler_t *game_handler);

#endif
