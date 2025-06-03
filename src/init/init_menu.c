/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init_menu
*/

#include "game.h"

static
bouton_t *set_buttons(img_t *released, void (*action)(game_handler_t *))
{
    bouton_t *bouton = malloc(sizeof(bouton_t));

    bouton->action = action;
    bouton->released = released;
    bouton->press = sfRectangleShape_create();
    sfRectangleShape_setPosition(bouton->press, (sfVector2f)
        {bouton->released->pos.x + 20.0, bouton->released->pos.y + 20.0});
    sfRectangleShape_setSize(bouton->press,
        (sfVector2f){bouton->released->rect.width - 35.0,
            bouton->released->rect.height - 30.0});
    sfRectangleShape_setOutlineThickness(bouton->press, 11.0);
    sfRectangleShape_setFillColor(bouton->press, sfRed);
    sfRectangleShape_setOutlineColor(bouton->press,
        sfTransparent);
    return bouton;
}

static
menu_t *init_menu(menu_t *menu, game_handler_t *game_h, char *title)
{
    menu->boutons = list_create();
    if (menu->boutons == NULL)
        return NULL;
    menu->background = malloc(sizeof(img_t));
    if (menu->background == NULL)
        return free(menu->boutons), NULL;
    menu->background = set_img(T_M_BG, (sfIntRect){0, 0, 1920, 1080},
    (sfVector2f){0, 0}, game_h);
    sfSprite_setScale(menu->background->sprite, (sfVector2f){1.3, 1.1});
    menu->text = set_txt(150, sfRed, (sfVector2f){960, 87}, title);
    return menu;
}

bool init_end_menu(menu_t *menu, game_handler_t *game_h)
{
    menu = init_menu(menu, game_h, "YOU WIN !");
    if (menu == NULL)
        return false;
    push_back(menu->boutons, set_buttons(set_img(T_B_HOME, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){650, 700}, game_h), &go_to_home));
    push_back(menu->boutons, set_buttons(set_img(T_B_EXIT, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){650, 850}, game_h), &exit_game));
        menu->boutons->tail->next = menu->boutons->head;
        menu->boutons->head->prev = menu->boutons->tail;
    menu->actual_bouton = menu->boutons->head;
    return true;
}

bool init_go_menu(menu_t *menu, game_handler_t *game_h)
{
    menu = init_menu(menu, game_h, "GAME OVER");
    if (menu == NULL)
        return false;
    push_back(menu->boutons, set_buttons(set_img(T_B_HOME, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){650, 700}, game_h), &go_to_home));
    push_back(menu->boutons, set_buttons(set_img(T_B_EXIT, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){650, 850}, game_h), &exit_game));
        menu->boutons->tail->next = menu->boutons->head;
        menu->boutons->head->prev = menu->boutons->tail;
    menu->actual_bouton = menu->boutons->head;
    return true;
}

static
void init_sound_button(menu_t *menu, game_handler_t *game_h)
{
    push_back(menu->boutons, set_buttons(set_img(T_ARR_L, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){500, 300}, game_h), &min_sound));
    push_back(menu->boutons, set_buttons(set_img(T_ARR_R, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){1300, 300}, game_h), &max_sound));
    push_back(menu->boutons, set_buttons(set_img(T_ARR_L, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){500, 450}, game_h), &min_music));
    push_back(menu->boutons, set_buttons(set_img(T_ARR_R, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){1300, 450}, game_h), &max_music));
}

bool init_settings_menu(menu_t *menu, game_handler_t *game_h)
{
    menu = init_menu(menu, game_h, "SETTINGS");
    if (menu == NULL)
        return false;
    init_sound_button(menu, game_h);
    push_back(menu->boutons, set_buttons(set_img(T_ARR_L, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){500, 600}, game_h), &min_win));
    push_back(menu->boutons, set_buttons(set_img(T_ARR_R, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){1300, 600}, game_h), &max_win));
    push_back(menu->boutons, set_buttons(set_img(T_B_BACK, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){650, 850}, game_h), &escape_set));
    menu->boutons->tail->next = menu->boutons->head;
    menu->boutons->head->prev = menu->boutons->tail;
    menu->actual_bouton = menu->boutons->head;
    return true;
}

bool init_pause_menu(menu_t *menu, game_handler_t *game_h)
{
    menu = init_menu(menu, game_h, "PAUSE");
    if (menu == NULL)
        return false;
    push_back(menu->boutons, set_buttons(set_img(T_B_HOME, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){650, 350}, game_h), &go_to_home));
    push_back(menu->boutons, set_buttons(set_img(T_B_SETTINGS, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){650, 500}, game_h), &go_to_settings));
    push_back(menu->boutons, set_buttons(set_img(T_B_BACK, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){650, 650}, game_h), &back_to_game));
    push_back(menu->boutons, set_buttons(set_img(T_B_EXIT, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){650, 800}, game_h), &exit_game));
    menu->boutons->tail->next = menu->boutons->head;
    menu->boutons->head->prev = menu->boutons->tail;
    menu->actual_bouton = menu->boutons->head;
    return true;
}

bool init_start_menu(menu_t *menu, game_handler_t *game_h)
{
    menu = init_menu(menu, game_h, "WOLF3D");
    if (menu == NULL)
        return false;
    push_back(menu->boutons, set_buttons(set_img(T_B_S1, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){1300, 300}, game_h), &handle_save1));
    push_back(menu->boutons, set_buttons(set_img(T_B_S2, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){1300, 450}, game_h), &handle_save2));
    push_back(menu->boutons, set_buttons(set_img(T_B_S3, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){1300, 600}, game_h), &handle_save3));
    push_back(menu->boutons, set_buttons(set_img(T_B_SETTINGS, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){150, 700}, game_h), &go_to_settings));
    push_back(menu->boutons, set_buttons(set_img(T_B_EXIT, (sfIntRect)
        {0, 0, 0, 0}, (sfVector2f){150, 850}, game_h), &exit_game));
    menu->boutons->tail->next = menu->boutons->head;
    menu->boutons->head->prev = menu->boutons->tail;
    menu->actual_bouton = menu->boutons->head;
    return true;
}
