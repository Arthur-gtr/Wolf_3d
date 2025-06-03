/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** free_screen
*/

#include "game.h"

static
void free_button(bouton_t *bouton)
{
    free_img(bouton->released);
    sfRectangleShape_destroy(bouton->press);
}

void free_list_buton(node_t *node)
{
    node_t *tmp = NULL;

    if (node == NULL)
        return;
    tmp = node->next;
    free_button((bouton_t *)node->data);
    free(node->data);
    free(node);
    return free_list_buton(tmp);
}

void free_list_text(node_t *node)
{
    node_t *tmp = NULL;

    if (node == NULL)
        return;
    tmp = node->next;
    sfText_destroy((sfText *)node->data);
    free(node);
    return free_list_text(tmp);
}

void free_music(sfMusic *music)
{
    sfMusic_stop(music);
    sfMusic_destroy(music);
}

void free_menu(menu_t *menu)
{
    menu->boutons->head->prev = NULL;
    menu->boutons->tail->next = NULL;
    free_list_buton(menu->boutons->head);
    free_img(menu->background);
    free(menu->background);
    sfText_destroy(menu->text);
    free(menu->boutons);
}

void free_screen(screen_t *screen)
{
    sfRenderWindow_destroy(screen->win);
    for (int i = 0; i != NB_MENU; i++){
        free_menu(&screen->menu[i]);
    }
    free_music(screen->menu_music);
    free_list_text(screen->text->head);
    free(screen->text);
    free(screen->menu);
}
