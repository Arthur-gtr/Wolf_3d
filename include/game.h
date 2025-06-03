/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** my
*/


#ifndef GAME_H
    #define GAME_H
    #include "entities.h"
    #include "call_csfml.h"
    #include "ray_casting.h"
    #include "controller.h"
    #include "menu.h"
    #include "level.h"
    #include "in_game.h"
    #include <stdbool.h>
    #define WINDOW_SIZE_X 1920
    #define WINDOW_SIZE_y 1080
    #define FPS_SET_60 16.666
    #define WALK 100
    #define RUN 200
    #define M_PI 3.14159265358979323846
    #define RAY_SCREEN (1980.0f / 1440.0f)
    #define DEG_TO_RAD(angle) ((angle) * (M_PI / 180.0))
    #define S_MENU 0
    #define S_LORE 1
    #define S_GAME 2
    #define WINM_FSCREEN 0
    #define WINM_BIG 1
    #define RST_CLOCK 0
    #define LET_CLOCK 1
    #define FLOOR 2
    #define CEILING 3

int wolf3d(void);
/*
** Entitie handler
** contient toute les
** entité
*/

typedef struct setting_s {
    float music_volume;
    float sound_volume;
    size_t win_mode;
} setting_t;

typedef struct screen_s {
    menu_t *menu;
    sfMusic *menu_music;
    size_t act_menu;
    size_t last_menu;
    sfRenderWindow *win;
    sfVideoMode win_mode;
    list_t *text;
    sfText *lore;
} screen_t;

typedef struct game_handler_s {
    sfEvent *event;
    time_management_t general_clock;
    ray_cast_t ray_cast;
    setting_t settings;
    int screen_mode;
    screen_t *screen;
    tab_texture_t **texture;
    tab_sound_t **sound;
    game_t *game;
    sfRectangleShape *square;
    controller_t controller;
}game_handler_t;

typedef struct floor_ceiling_s {
    sfVector2f ray_dir_0;
    sfVector2f ray_dir_1;
    int p;
    float pos_z;
    float row_dist;
    sfVector2f floor_step;
    sfVector2f floor;
    sfColor color;
    sfVector2i cell;
    sfVector2i tex;
} floor_ceiling_t;

typedef struct entities_class_s entities_class_t;

typedef struct game_mode_s {
    int (*funct)(game_handler_t *);
} game_mode_t;

int launch_game(game_handler_t *game_handler);

/*Game mode*/
int choose_window_mode(game_handler_t *game_handler);
int display_full_map(game_handler_t *game_handler);
int display_menu(game_handler_t *g_handler);
int run_game(game_handler_t *g_h);
int draw_lore(game_handler_t *g_h);

/*Player*/
void player_interaction(entities_t *player, game_handler_t *g_h);
void new_rotate_player(entities_t *player, float rot_speed,
    sfInt32 time);
void animate_shgun(game_handler_t *g_h, gun_t *shotgun);
void animate_gun(game_handler_t *g_h, gun_t *gun);
void animate_minigun(game_handler_t *g_h, gun_t *gun);

/*3D*/
float get_coord_wall(entities_t *entities, float angle, int precision);
int display_3d_map(game_handler_t *game_handler);
void free_game(game_handler_t *game_handler);
void check_back_to_menu(game_handler_t *handler);
void draw_hud(hud_t *hud, game_handler_t *g_h);
void draw_floor(entities_t *player, ray_cast_t *ray_cast,
    tab_texture_t **tab_texture);


/*Draw sprite*/
void draw_sprite(game_handler_t *game, sfRenderWindow *window);
void put_color_in_buffer(sfUint8 *array_pixel,
    sfColor new_pixel, int index_storage, int dist);

/*Call all draw funct*/
void draw_screen(game_handler_t *game);

/*get*/
sfVector2f get_coord(sfVector2f coord_window);
bool is_in_real_wall(sfVector2f coord);

/*Controller*/
bool check_l3(void);
bool check_l2(void);
bool check_l1(void);
sfUint8 get_left_stick(void);

bool check_r3(void);
bool check_r2(void);
bool check_r1(void);
sfUint8 get_right_stick(void);

/*Time and clock*/
bool need_refresh_clock(time_management_t *sound_clock, float sec_reset);

/*free*/
void free_screen(screen_t *screen);
void free_img(img_t *img);

#endif //GAME_H
