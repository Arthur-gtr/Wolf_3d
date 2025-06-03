/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** my
*/


#ifndef INIT_H
    #define INIT_H

    #include "call_csfml.h"
    #include "game.h"

sfRenderWindow *create_window(void);
int init_game_handler(game_handler_t *game_handler);
bool init_player(game_handler_t *g_h);
int init_wall(object_t *wall);
time_management_t init_clock(void);
int init_wall(object_t *wall);
tab_texture_t **init_textures(void);
tab_sound_t **init_sound(void);
sfMusic *init_music(char *file, game_handler_t *g_h);
gun_t **init_weapons(game_handler_t *g_h);
bool load_map(game_handler_t *g_h);
bool parsing_map(game_handler_t *g_h);
bool init_game(game_handler_t *g_h, char *save_dir);
bool init_ray_buffer(ray_cast_t *ray_cast);
bool init_hud(game_handler_t *g_h);
void free_entities(entities_t *ent);
bool init_lore(screen_t *screen);

#endif //INIT_H
