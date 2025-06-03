/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** init_player_ennemies
*/
#include "game.h"
#include "entities.h"
#include "init.h"

static
entities_t *init_entities(sfVector2f coord, sfVector2f h_b, size_t id,
    img_t *img)
{
    entities_t *entities = malloc(sizeof(entities_t));

    if (entities == NULL)
        return NULL;
    entities->img = img;
    entities->id = id;
    entities->angle = 0;
    entities->speed = WALK;
    entities->coord = (sfVector2f){coord.x + 0.5, coord.y + 0.5};
    entities->hb_2d = h_b;
    entities->clock = init_clock();
    entities->dir = (sfVector2f){-1.0, 0.0};
    entities->plan = (sfVector2f){0.0, 0.66};
    return entities;
}

static
inventory_t *init_inventory(game_handler_t *g_h)
{
    inventory_t *inventory = malloc(sizeof(inventory_t));

    if (inventory == NULL)
        return NULL;
    inventory->gun = malloc(sizeof(gun_t) * NB_GUN);
    if (g_h->game->have_been_f || !load_from_file(g_h, "nb_gun.bin",
        &inventory->nb_of_gun, sizeof(inventory->nb_of_gun)))
        inventory->nb_of_gun = 2;
    inventory->actual_gun = W_ID_KNIFE;
    inventory->gun = init_weapons(g_h);
    inventory->clock_refill = init_clock();
    inventory->clock_shoot = init_clock();
    return inventory;
}

bool init_player(game_handler_t *g_h)
{
    g_h->game->ent->player = malloc(sizeof(player_t));
    if (g_h->game->ent->player == NULL)
        return false;
    g_h->game->ent->player->property = init_entities((sfVector2f){5, 5},
        (sfVector2f){0.4, 0.4}, ID_PLAYER, set_img(T_P_2D,
        (sfIntRect){0, 0, 0, 0}, (sfVector2f){0.3, 0.3}, g_h));
    g_h->game->ent->player->clock_sound = init_clock();
    g_h->game->ent->player->inventory = init_inventory(g_h);
    g_h->game->ent->player->is_shooting = false;
    g_h->game->ent->player->property->angle = 0.0;
    if (g_h->game->ent->player->inventory == NULL)
        return false;
    g_h->game->ent->player->property->life = 100;
    return true;
}

static
ennemies_t *set_ss(game_handler_t *g_h, ennemies_t *ennemi,
    sfVector2f coord)
{
    ennemi->property = init_entities(coord, (sfVector2f){0.5, 0.5}, ID_SS,
        set_img(T_SS, (sfIntRect){0, 0, 65, 65}, coord, g_h));
    ennemi->clock_search = init_clock();
    ennemi->property->life = 45;
    ennemi->is_shooting = false;
    ennemi->last_frame_shooting = false;
    ennemi->property->speed = WALK + 25;
    ennemi->clock_touch = init_clock();
    ennemi->clock_shoot = init_clock();
    ennemi->clock_search = init_clock();
    ennemi->clock_move = init_clock();
    ennemi->anim = 0;
    ennemi->gun_shot = &gun_shoot;
    return ennemi;
}

static
ennemies_t *set_mutant(game_handler_t *g_h, ennemies_t *ennemi,
    sfVector2f coord)
{
    ennemi->property = init_entities(coord, (sfVector2f){0.5, 0.5}, ID_MUTANT
        , set_img(T_MUTANT, (sfIntRect){0, 0, 65, 65}, coord, g_h));
    ennemi->clock_search = init_clock();
    ennemi->property->life = 55;
    ennemi->property->speed = RUN;
    ennemi->is_shooting = false;
    ennemi->last_frame_shooting = false;
    ennemi->clock_touch = init_clock();
    ennemi->clock_shoot = init_clock();
    ennemi->clock_search = init_clock();
    ennemi->clock_move = init_clock();
    ennemi->anim = 0;
    ennemi->gun_shot = &assault_shoot;
    return ennemi;
}

static
ennemies_t *set_brut(game_handler_t *g_h, ennemies_t *ennemi,
    sfVector2f coord)
{
    ennemi->property = init_entities(coord, (sfVector2f){0.7, 0.7}, ID_BRUT,
        set_img(T_BRUT, (sfIntRect){0, 0, 65, 65}, coord, g_h));
    ennemi->clock_search = init_clock();
    ennemi->property->life = 75;
    ennemi->property->speed = WALK - 25;
    ennemi->clock_touch = init_clock();
    ennemi->clock_shoot = init_clock();
    ennemi->clock_search = init_clock();
    ennemi->clock_move = init_clock();
    ennemi->is_shooting = false;
    ennemi->last_frame_shooting = false;
    ennemi->anim = 0;
    ennemi->gun_shot = &minigun_shoot;
    return ennemi;
}

static
bool init_ennemies(game_handler_t *g_h, sfVector2f coord, int id)
{
    ennemies_t *ennemies = malloc(sizeof(ennemies_t));

    if (ennemies == NULL)
        return fprintf(stderr, "malloc error"), false;
    if (id == ID_SS)
        ennemies = set_ss(g_h, ennemies, coord);
    if (id == ID_MUTANT)
        ennemies = set_mutant(g_h, ennemies, coord);
    if (id == ID_BRUT)
        ennemies = set_brut(g_h, ennemies, coord);
    if (ennemies == NULL)
        return fprintf(stderr, "no ennemi id"), false;
    push_back(g_h->game->ent->entities, ennemies->property);
    push_back(g_h->game->ent->ennemies, ennemies);
    return true;
}

static
void choose_parsing(game_handler_t *g_h, int x, int y)
{
    if (g_h->game->level.map[g_h->game->level.actual_level][y][x] >= ID_SS &&
        g_h->game->level.map[g_h->game->level.actual_level][y][x] <= ID_BRUT)
        if (!init_ennemies(g_h, (sfVector2f){x, y},
            g_h->game->level.map[g_h->game->level.actual_level][y][x]))
            return;
    if (g_h->game->level.map[g_h->game->level.actual_level][y][x] ==
        ID_PLAYER)
        g_h->game->ent->player->property->coord =
            (sfVector2f){x + 1.5, y + 0.5};
}

bool parsing_map(game_handler_t *g_h)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
        for (int x = 0; x < MAP_WIDTH; x++)
            choose_parsing(g_h, x, y);
    return true;
}
