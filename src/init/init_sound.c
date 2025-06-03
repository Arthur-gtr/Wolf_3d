/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** init_sound
*/

#include "game.h"
#include "init.h"
#include "call_csfml.h"
#include "utils.h"

const tab_sound_t TAB_SOUND[] = {
    {NULL, NULL, SO_B_MOVE, "./sound/menu/button_click.ogg"},
    {NULL, NULL, SO_B_CLICK, "./sound/menu/button_move.ogg"},
    {NULL, NULL, SO_B_P_STEP, "./sound/player_step.ogg"},
    {NULL, NULL, SO_KNIFE, "./sound/weapons/knife_sound.ogg"},
    {NULL, NULL, SO_GUN, "./sound/weapons/gun_sound.ogg"},
    {NULL, NULL, SO_SHOTGUN, "./sound/weapons/shotgun_sound.ogg"},
    {NULL, NULL, SO_MINIGUN, "./sound/weapons/minigun_sound.ogg"},
    {NULL, NULL, SO_DIYING, "./sound/die_sound.ogg" },
    {NULL, NULL, SO_ASSAULT, "./sound/weapons/assault_sound.ogg"},
    {NULL, NULL, SO_OBJ, "./sound/obj_take.ogg"},
    {NULL, NULL, 0, NULL}
};

const size_t SZ_TAB_SOUND = sizeof TAB_SOUND / sizeof *TAB_SOUND;

tab_sound_t *dup_sound(const tab_sound_t sound)
{
    tab_sound_t *new_tab = malloc(sizeof(tab_sound_t));

    if (new_tab == NULL)
        return NULL;
    new_tab->id = sound.id;
    new_tab->buffer = NULL;
    new_tab->sound = NULL;
    new_tab->file = NULL;
    if (sound.file == NULL)
        return new_tab;
    new_tab->file = my_strdup(sound.file);
    if (new_tab->file == NULL)
        return free(new_tab), NULL;
    new_tab->buffer = sfSoundBuffer_createFromFile(new_tab->file);
    new_tab->sound = sfSound_create();
    sfSound_setBuffer(new_tab->sound, new_tab->buffer);
    return new_tab;
}

tab_sound_t **init_sound(void)
{
    tab_sound_t **sound = malloc(sizeof(tab_texture_t *) * SZ_TAB_SOUND + 1);

    if (sound == NULL)
        return NULL;
    for (size_t i = 0; i < SZ_TAB_SOUND; i++){
        sound[i] = dup_sound(TAB_SOUND[i]);
        if (sound[i] == NULL)
            return NULL;
    }
    sound[SZ_TAB_SOUND - 1] = NULL;
    return sound;
}
