/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** manege_ennemi_touch
*/
#include "game.h"

static
void anim_little_death(ennemies_t *ent, game_handler_t *g_h)
{
    g_h->game->ent->player->inventory->gun[W_ID_GUN]->ammo += 15;
    ent->property->img->rect.top = ent->property->img->rect.height * 5;
    ent->property->img->rect.left =
        ent->property->img->rect.width * 2;
    sfClock_restart(ent->clock_touch.clock);
}

static
void anim_big_death(ennemies_t *ent, game_handler_t *g_h)
{
    if (g_h->game->ent->player->inventory->nb_of_gun < W_ID_MINIGUN - 1)
        g_h->game->ent->player->inventory->gun[W_ID_GUN]->ammo += 25;
    else {
        g_h->game->ent->player->inventory->gun[W_ID_SHOTGUN]->ammo += 10;
        g_h->game->ent->player->inventory->gun[W_ID_MINIGUN]->ammo += 100;
    }
    g_h->game->score.score += 500;
    ent->property->img->rect.top = ent->property->img->rect.height * 2;
    ent->property->img->rect.left = 0;
    sfClock_restart(ent->clock_touch.clock);
}

static
void anim_touch(ennemies_t *ent)
{
    if (ent->property->id == ID_SS){
        ent->property->img->rect.left =
        ent->property->img->rect.width * ent->anim;
        ent->property->img->rect.top = ent->property->img->rect.height * 5;
    }
    if (ent->property->id == ID_MUTANT){
        ent->property->img->rect.left = 0;
        ent->property->img->rect.top =
        ent->property->img->rect.height * (5 + ent->anim);
    }
    ent->anim = (ent->anim + 1) % 2;
    sfClock_restart(ent->clock_touch.clock);
}

void manage_ennemi_touch(ennemies_t *ent, size_t damage, game_handler_t *g_h)
{
    ent->property->life -= damage;
    if (ent->property->life <= 0){
        if (ent->property->id == ID_BRUT)
            return anim_big_death(ent, g_h);
        if (ent->property->id == ID_SS)
            g_h->game->score.score += 100;
        if (ent->property->id == ID_MUTANT)
            g_h->game->score.score += 200;
        anim_little_death(ent, g_h);
        sfSound_play(get_sound(g_h->sound, SO_DIYING));
        return;
    }
    ent->is_shooting = true;
    if (ent->property->id == ID_BRUT)
        return;
    ent->clock_touch.time = sfClock_getElapsedTime(ent->clock_touch.clock);
    if (ent->clock_touch.time.microseconds / 1000.0 > 100.0)
        anim_touch(ent);
}
