/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_game
*/

#include "game.h"

void free_entities(entities_t *ent)
{
    sfSprite_destroy(ent->img->sprite);
    sfClock_destroy(ent->clock.clock);
    free(ent->img);
    free(ent);
}

void save_game(game_t *game, game_handler_t *g_h, int finish)
{
    g_h->game->have_been_f = finish;
    save_to_file(g_h, "have_been_f.bin", &finish,
            sizeof(finish));
    save_to_file(g_h, "score_nb.bin", &game->score.score,
        sizeof(game->score.score));
    save_to_file(g_h, "score_time.bin", &game->score.score_mili_s,
        sizeof(game->score.score_mili_s));
    save_to_file(g_h, "actual_level.bin", &game->level.actual_level,
        sizeof(game->level.actual_level));
    save_to_file(g_h, "nb_gun.bin", &game->ent->player->inventory->nb_of_gun,
        sizeof(game->ent->player->inventory->nb_of_gun));
    for (int i = W_ID_GUN; i < NB_GUN; i++)
        save_to_file(g_h, g_h->game->ent->player->inventory->gun[i]->save_file
            , &g_h->game->ent->player->inventory->gun[i]->ammo,
            sizeof(g_h->game->ent->player->inventory->gun[i]->ammo));
}

void free_game(game_handler_t *g_h)
{
    free(g_h->game->actual_save);
}
