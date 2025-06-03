/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** utils
*/
#include "game.h"
#include "call_csfml.h"

sfText *set_txt(size_t size, sfColor color, sfVector2f position, char *str)
{
    sfText *txt = sfText_create();
    sfFloatRect bounds;
    sfFont *font = sfFont_createFromFile("font/alagard.ttf");

    if (!txt || !font)
        exit(84);
    sfText_setFont(txt, font);
    sfText_setCharacterSize(txt, size);
    sfText_setColor(txt, color);
    sfText_setPosition(txt, position);
    sfText_setString(txt, str);
    sfText_setOutlineColor(txt, sfBlack);
    bounds = sfText_getLocalBounds(txt);
    sfText_setOrigin(txt, (sfVector2f){bounds.width / 2.0f,
        bounds.height / 2.0f});
    sfText_setOutlineThickness(txt, size / 10);
    return txt;
}

img_t *set_img(size_t texture_token, sfIntRect rect, sfVector2f pos,
    game_handler_t *g_h)
{
    img_t *img = malloc(sizeof(img_t));

    img->rect = rect;
    img->pos = pos;
    img->sprite = sfSprite_create();
    img->texture = get_texture(g_h->texture, texture_token);
    sfSprite_setTexture(img->sprite, img->texture, false);
    if (rect.width == 0){
        img->rect = sfSprite_getTextureRect(img->sprite);
    }
    sfSprite_setTextureRect(img->sprite, img->rect);
    img->img = sfTexture_copyToImage(img->texture);
    sfSprite_setPosition(img->sprite, img->pos);
    return img;
}

sfTexture *get_texture(tab_texture_t **tab, size_t token)
{
    for (int i = 0; tab[i]; i++){
        if (tab[i]->id == token)
            return tab[i]->texture;
    }
    fprintf(stderr, "no texture token");
    return NULL;
}

sfSound *get_sound(tab_sound_t **tab, size_t token)
{
    for (int i = 0; tab[i]; i++)
        if (tab[i]->id == token)
            return tab[i]->sound;
    fprintf(stderr, "no sound token");
    return NULL;
}
