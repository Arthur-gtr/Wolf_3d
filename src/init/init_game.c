/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_game
*/

#include "game.h"
#include "init.h"
#include "call_csfml.h"
#include "string.h"

static
score_t init_score_and_save(game_handler_t *g_h)
{
    score_t score;

    if (!load_from_file(g_h, "have_been_f.bin",
        &g_h->game->have_been_f, sizeof(g_h->game->have_been_f)))
        g_h->game->have_been_f = 0;
    if (g_h->game->have_been_f || !load_from_file(g_h, "score_nb.bin",
        &score.score, sizeof(score.score)))
        score.score = 0;
    if (g_h->game->have_been_f || !load_from_file(g_h, "score_time.bin",
            &score.score_mili_s, sizeof(score.score_mili_s)))
        score.score_mili_s = 1;
    score.time_to_end = init_clock();
    return score;
}

static
img_t **init_weapons_two_d(game_handler_t *g_h, float scale_x, float scale_y,
    sfVector2u window_size)
{
    img_t **wp_two_d = malloc(sizeof(img_t *) * NB_GUN);

    if (wp_two_d == NULL)
        return NULL;
    wp_two_d[0] = set_img(T_2D_KNIFE, (sfIntRect){0, 0, 0, 0}
        , (sfVector2f){1620 * scale_x, window_size.y - (225 * scale_y)}, g_h);
    wp_two_d[1] = set_img(T_2D_GUN, (sfIntRect){0, 0, 0, 0}
        , (sfVector2f){1640 * scale_x, window_size.y - (212 * scale_y)}, g_h);
    wp_two_d[2] = set_img(T_2D_SHOTGUN, (sfIntRect){0, 0, 0, 0}
        , (sfVector2f){1605 * scale_x, window_size.y - (160 * scale_y)}, g_h);
    wp_two_d[3] = set_img(T_2D_MINIGUN, (sfIntRect){0, 0, 0, 0}
        , (sfVector2f){1580 * scale_x, window_size.y - (160 * scale_y)}, g_h);
    sfSprite_setScale(wp_two_d[0]->sprite, (sfVector2f){11.5, 11.5});
    sfSprite_setScale(wp_two_d[1]->sprite, (sfVector2f){11.5, 11.5});
    sfSprite_setScale(wp_two_d[2]->sprite, (sfVector2f){8, 8});
    sfSprite_setScale(wp_two_d[3]->sprite, (sfVector2f){7.25, 7.25});
    if (!wp_two_d[0] || !wp_two_d[1] || !wp_two_d[2] || !wp_two_d[3])
        return free(wp_two_d), NULL;
    return wp_two_d;
}

void scale_hud(hud_t *hud, float scale_x, float scale_y)
{
    sfSprite_setScale(hud->bg_player_info->sprite, (sfVector2f){9, 5.5});
    sfText_setScale(hud->life, (sfVector2f){1.5 * scale_x, 1.5 * scale_y});
    sfText_setScale(hud->score, (sfVector2f){1.5 * scale_x, 1.5 * scale_y});
    sfText_setScale(hud->magazine, (sfVector2f){1.5 * scale_x, 1.5 * scale_y});
    sfText_setScale(hud->ammo, (sfVector2f){1.5 * scale_x, 1.5 * scale_y});
    sfText_setScale(hud->score, (sfVector2f){0.75 * scale_x, 0.75 * scale_y});
    sfText_setScale(hud->time, (sfVector2f){0.75 * scale_x, 0.75 * scale_y});
}

static
void init_text_base_hud(game_handler_t *g_h, float scale_x, float scale_y,
    sfVector2u window_size)
{
    g_h->game->hud->magazine = set_txt(80, sfColor_fromRGB(255, 255, 255),
        (sfVector2f){1040 * scale_x, window_size.y - (90 * scale_y)}, "6");
    g_h->game->hud->life = set_txt(80, sfColor_fromRGB(255, 0, 0),
            (sfVector2f){670 * scale_x, window_size.y - (110 * scale_y)}, "0");
    g_h->game->hud->time = set_txt(80, sfColor_fromRGB(105, 105, 105),
        (sfVector2f){50 * scale_x, 90 * scale_y}, "0.0");
    g_h->game->hud->score = set_txt(80, sfColor_fromRGB(105, 105, 105),
        (sfVector2f){30 * scale_x, 30 * scale_y}, "0");
    g_h->game->hud->ammo = set_txt(80, sfColor_fromRGB(105, 105, 105),
        (sfVector2f){230 * scale_x, window_size.y - (110 * scale_y)}, "6");
}

static
void init_w_anim(game_handler_t *g_h)
{
    g_h->game->hud->y_move = (sfVector2f){950.0, 970.0};
    g_h->game->hud->to_move = 2.0;
    g_h->game->hud->animation = sfClock_create();
    g_h->game->hud->anim = false;
    g_h->game->clock_game = sfClock_create();
}

static
void init_level_launch(hud_t *hud)
{
    sfFloatRect size;
    sfFont *font = sfFont_createFromFile("font/title.ttf");

    hud->Level_txt = set_txt(400, sfColor_fromRGB(250, 157, 0),
        (sfVector2f){0, 0}, "LEVEL 1");
    size = sfText_getLocalBounds(hud->Level_txt);
    sfText_setOrigin(hud->Level_txt, (sfVector2f)
        {size.width / 2, size.height});
    sfText_setPosition(hud->Level_txt, (sfVector2f){WIDTH / 2, HEIGHT / 2});
    sfText_setFont(hud->Level_txt, font);
    hud->level_launch = init_clock();
}

bool init_hud(game_handler_t *g_h)
{
    player_t *player = g_h->game->ent->player;
    sfVector2u window_size = sfRenderWindow_getSize(g_h->screen->win);
    float scale_x = (float)window_size.x / (float)WINDOW_SIZE_X;
    float scale_y = (float)window_size.y / (float)WINDOW_SIZE_y;

    g_h->game->hud = malloc(sizeof(hud_t));
    if (g_h->game->hud == NULL)
        return false;
    g_h->game->hud->bg_player_info = set_img(T_HUD, (sfIntRect){0, 0, 0, 0},
        (sfVector2f){0, 910}, g_h);
    g_h->game->hud->weapon_two_d = init_weapons_two_d(g_h,
        scale_x, scale_y, window_size);
    g_h->game->hud->actual_weapon =
    g_h->game->hud->weapon_two_d[player->inventory->actual_gun];
    init_w_anim(g_h);
    init_text_base_hud(g_h, scale_x, scale_y, window_size);
    scale_hud(g_h->game->hud, scale_x, scale_y);
    init_level_launch(g_h->game->hud);
    return true;
}

static
entities_handler_t *init_handler(void)
{
    entities_handler_t *ent = malloc(sizeof(entities_handler_t));

    if (ent == NULL)
        return NULL;
    ent->ennemies = list_create();
    if (ent->ennemies == NULL)
        return free(ent), NULL;
    ent->entities = list_create();
    if (ent->entities == NULL)
        return free(ent), NULL;
    ent->object = list_create();
    if (ent->object == NULL)
        return free(ent), NULL;
    return ent;
}

bool init_game(game_handler_t *g_h, char *save_dir)
{
    g_h->game = malloc(sizeof(game_t));
    if (g_h->game == NULL)
        return false;
    g_h->game->ent = init_handler();
    g_h->game->clock_game = NULL;
    g_h->game->actual_save = strdup(save_dir);
    g_h->game->score = init_score_and_save(g_h);
    if (g_h->game->ent == NULL)
        return false;
    g_h->game->game_music = init_music("sound/game_music.ogg", g_h);
    if (!load_map(g_h))
        return false;
    if (!init_player(g_h))
        return false;
    if (!parsing_map(g_h))
        return false;
    if (!init_hud(g_h) || !init_ray_buffer(&g_h->ray_cast))
        return false;
    return true;
}
