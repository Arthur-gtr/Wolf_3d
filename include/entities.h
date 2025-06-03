/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** my
*/

#ifndef ENTITIES_H
    #define ENTITIES_H
    #include "call_csfml.h"
    #include "time.h"
    #include "utils.h"
    #include "my.h"
    #define ID_WALL 1
    #define ID_WALL_FLAG_ARCH ID_WALL + 1
    #define ID_WALL_BRICK ID_WALL_FLAG_ARCH + 1
    #define ID_WALL_BRICK2 ID_WALL_BRICK + 1
    #define ID_PLAYER ID_WALL_BRICK2 + 1
    #define ID_SS ID_PLAYER + 1
    #define ID_MUTANT ID_SS + 1
    #define ID_BRUT ID_MUTANT + 1
    #define ID_AMMO ID_BRUT +1
    #define ID_LIFE ID_AMMO +1
    #define ID_WEAPON_OBJ ID_LIFE + 1
    #define ID_PLAYER_MOVE 0
    #define ID_ENNEMIE_MOVE 1
    #define ID_OBJECT_MOVE 2
    #define W_ID_KNIFE 0
    #define W_ID_GUN 1
    #define W_ID_SHOTGUN 2
    #define W_ID_MINIGUN 3
    #define D_KNIFE 50
    #define D_GUN 20
    #define D_SHOTGUN 100
    #define D_MINIGUN 2
    #define D_ASSAULT 3
    #define NB_GUN 4

typedef struct game_s game_t;
typedef struct ennemies_s ennemies_t;
typedef struct game_handler_s game_handler_t;
typedef struct player_s player_t;

typedef struct entities_s {
    sfVector2f coord;
    img_t *img;
    time_management_t clock;
    sfVector2f hb_2d;
    float angle;
    double distance;
    int speed;
    int life;
    int id;
    sfVector2f dir;
    sfVector2f plan;
}entities_t;

typedef struct gun_s {
    int ammo;
    int magazine;
    int mag_cap;
    int (*gun_shot)(player_t *, ennemies_t *, game_handler_t *);
    sfSound *shoot_so;
    img_t *img;
    char *save_file;
} gun_t;

typedef struct inventory_s {
    int nb_of_gun;
    int actual_gun;
    time_management_t clock_shoot;
    time_management_t clock_refill;
    gun_t **gun;
} inventory_t;

typedef struct player_s {
    bool is_shooting;
    entities_t *property;
    inventory_t *inventory;
    time_management_t clock_sound;
}player_t;

typedef struct ennemies_s {
    bool is_shooting;
    bool last_frame_shooting;
    int anim;
    entities_t *property;
    int (*gun_shot)(player_t *, ennemies_t *, game_handler_t *);
    time_management_t clock_search;
    time_management_t clock_shoot;
    time_management_t clock_touch;
    time_management_t clock_move;
}ennemies_t;

typedef struct object_s {
    entities_t *property;
    void (*effect)(game_handler_t *, node_t *);
}object_t;

typedef struct entities_handler_s {
    player_t *player;
    list_t *object;
    list_t *ennemies;
    list_t *entities;
}entities_handler_t;


typedef struct angle_sprite_s {
    sfVector2f angle_interval;
    int sprite_coef;
} angle_sprite_t;

bool launch_e_shoot(ennemies_t *en, float millisec_to_wait,
    game_handler_t *g_h, size_t token_sound);
bool launch_p_shoot(inventory_t *inv, float millisec_to_wait,
    game_handler_t *g_h, size_t token_sound);

ennemies_t *shoot_ray(game_handler_t *game, entities_t *player);
int knife_shoot(player_t *player, ennemies_t *shooter, game_handler_t *g_h);
int gun_shoot(player_t *player, ennemies_t *shooter, game_handler_t *g_h);
int shotgun_shoot(player_t *player, ennemies_t *shooter, game_handler_t *g_h);
int minigun_shoot(player_t *player, ennemies_t *shooter, game_handler_t *g_h);
int assault_shoot(player_t *player, ennemies_t *shooter, game_handler_t *g_h);
void handle_player_shooting(game_handler_t *g_h);
void handle_ent_event(game_handler_t *game_handler, entities_handler_t *ent);
void manage_ennemi_touch(ennemies_t *ent, size_t damage, game_handler_t *g_h);
void new_moove_up(entities_t *entities, sfInt32 tim_mili, int map[20][20]);
void new_moove_down(entities_t *entities, sfInt32 tim_mili, int map[20][20]);
void new_moove_left(entities_t *entities, sfInt32 tim_mili, int map[20][20]);
void new_moove_right(entities_t *entities, sfInt32 tim_mili, int map[20][20]);
bool search_player(game_handler_t *game, entities_t *ennemie);
ennemies_t *shoot_ray(game_handler_t *game, entities_t *player);
void anim_shoot_mutant(ennemies_t *ennemi);
void anim_shoot_ss(ennemies_t *ennemi);
void anim_shoot_brut(ennemies_t *ennemi);
void move_ennemies(ennemies_t *ennemies, game_handler_t *g_h);
void rotate_right(entities_t *player, float rot_speed);
void rotate_left(entities_t *player, float rot_speed);

#endif //ENTITIES_H
