/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** draw_lore
*/

#include "game.h"

int draw_lore(game_handler_t *g_h)
{
    sfRenderWindow_drawSprite(g_h->screen->win,
        g_h->screen->menu->background->sprite, NULL);
    sfRenderWindow_drawText(g_h->screen->win, g_h->screen->lore,
        NULL);
    if (sfKeyboard_isKeyPressed(sfKeyEnter)) {
            g_h->screen_mode = S_MENU;
            g_h->screen->act_menu = M_START;
            }
    return 1;
}

bool init_lore(screen_t *screen)
{
    screen->lore = set_txt(50, sfColor_fromRGB(255, 255, 255),
        (sfVector2f){960, 540},
        "1940, la seconde guerre mondiale est a son paroxysme,\n"
        "le Troisieme Reich mene des experiences terrifiantes dans\n"
        "le chateau de Wolfenstein, une forteresse sinistre perdue\n"
        "au coeur de l'Allemagne nazie.\n"
        "Un agent de l'OSS (Office of Strategic Services), est capture\n"
        "lors d'une mission d'infiltration.\n"
        "Enferme dans les geoles du chateau, il s'evade, seul contre tous.\n"
        "Arme de courage, de quelques munitions et d'une rage froide,\n"
        "il entame une traversee du complexe pour s'evader et devoiler\n"
        "tout ce qu'il a vu.");
    if (!screen->lore)
        return false;
    return true;
}
