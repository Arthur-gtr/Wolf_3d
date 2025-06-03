/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** display_menu
*/

#include "game.h"
#include "call_csfml.h"
#include "controller.h"

void draw_menu(menu_t *menu, game_handler_t *g_h)
{
    int len = menu->boutons->size;

    sfRenderWindow_drawSprite(g_h->screen->win, menu->background->sprite,
        NULL);
    sfRenderWindow_drawText(g_h->screen->win, menu->text, NULL);
    sfRenderWindow_drawRectangleShape(g_h->screen->win,
        ((bouton_t *)menu->actual_bouton->data)->press, NULL);
    for (node_t *cur = menu->boutons->head; len > 0; len--){
        sfRenderWindow_drawSprite(g_h->screen->win,
            ((bouton_t *)cur->data)->released->sprite, NULL);
        cur = cur->next;
    }
    for (node_t *cur = g_h->screen->text->head
        ; cur && g_h->screen->act_menu == M_SETTING; cur = cur->next)
        sfRenderWindow_drawText(g_h->screen->win, cur->data, NULL);
}

void handle_menu_event(menu_t *menu, game_handler_t *g_h, sfUint8 controller)
{
    if (g_h->event->key.code == sfKeyDown || (controller & DOWN)){
        menu->actual_bouton = menu->actual_bouton->next;
        sfSound_play(get_sound(g_h->sound, SO_B_MOVE));
    }
    if (g_h->event->key.code == sfKeyUp || (controller & UP)){
        menu->actual_bouton = menu->actual_bouton->prev;
        sfSound_play(get_sound(g_h->sound, SO_B_MOVE));
    }
    if (g_h->event->key.code == sfKeyEnter || check_cross() == true){
        sfSound_play(get_sound(g_h->sound, SO_B_CLICK));
        ((bouton_t *)menu->actual_bouton->data)->action(g_h);
    }
}

int display_menu(game_handler_t *g_h)
{
    draw_menu(&g_h->screen->menu[g_h->screen->act_menu], g_h);
    return 0;
}
