/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** run_game
*/

#include "game.h"
#include "ray_casting.h"
#include "entities.h"
#include "init.h"

/*
static
sfInt32 get_milisc_clock(time_management_t time_manage)
{
    sfclokc sfClock_getElapsedTime(entities->clock.clock);
    sfTime_asMilliseconds(entities->clock.clock);
}
*/

void free_ent_handler(entities_handler_t *ent)
{
    node_t *next = NULL;

    for (node_t *cur = ent->entities->head; cur; cur = next){
        next = cur->next;
        free_entities(cur->data);
        destroy_nodes(ent->entities, cur);
    }
}

static
bool check_end(game_handler_t *g_h)
{
    g_h->screen->act_menu = M_END;
    save_game(g_h->game, g_h, true);
    sfSprite_setTexture(g_h->screen->menu[M_END].background->sprite,
        g_h->ray_cast.screen_text, sfTrue);
    g_h->screen_mode = S_MENU;
    return true;
}

static
bool pass_level(game_handler_t *g_h)
{
    if (g_h->game->ent->ennemies->size <= 0){
        if (g_h->game->level.actual_level >= NB_MAP - 1
            && g_h->game->have_been_f == false)
            return check_end(g_h);
        if (!(g_h->game->level.actual_level < NB_MAP - 1)
            && g_h->game->have_been_f == true)
            return true;
        g_h->game->ent->player->inventory->nb_of_gun++;
        if (g_h->game->ent->player->inventory->nb_of_gun >= NB_GUN)
            g_h->game->ent->player->inventory->nb_of_gun = NB_GUN;
        g_h->game->level.actual_level += 1;
        g_h->game->ent->player->property->life = 100;
        sfClock_restart(g_h->game->hud->level_launch.clock);
        save_game(g_h->game, g_h, false);
        free_ent_handler(g_h->game->ent);
        parsing_map(g_h);
        return false;
    }
    return false;
}

bool check_die(game_handler_t *g_h)
{
    if (g_h->game->ent->player->property->life > 0)
        return false;
    g_h->screen->act_menu = M_GO;
    g_h->screen_mode = S_MENU;
    return true;
}

int run_game(game_handler_t *g_h)
{
    if (pass_level(g_h))
        return 0;
    if (check_die(g_h))
        return 0;
    if (sfClock_getElapsedTime(g_h->game->hud->level_launch.clock)
        .microseconds / 1000.0 > 2000.0){
        handle_ent_event(g_h, g_h->game->ent);
        handle_player_shooting(g_h);
        player_interaction(g_h->game->ent->player->property, g_h);
    }
    execute_ray(g_h, g_h->game->ent->player->property);
    draw_screen(g_h);
    return 0;
}
