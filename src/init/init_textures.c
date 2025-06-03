/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** init_textures
*/
#include "game.h"
#include "init.h"
#include "call_csfml.h"

tab_texture_t const TAB_TEXTURE[] = {
    {NULL, NULL, WALL_IRON, "./img/wall/libdoor.png"},
    {NULL, NULL, WALL_FLAG_ARCH, "./img/wall/flag_wall_arch.png"},
    {NULL, NULL, WALL_BRICK, "./img/wall/brickstone.png"},
    {NULL, NULL, WALL_BRICK2, "./img/wall/brickstone2.png"},
    {NULL, NULL, T_BRUT, "./img/ent/Brut.png"},
    {NULL, NULL, T_MUTANT, "./img/ent/Mutant.png"},
    {NULL, NULL, T_SS, "./img/ent/SS_ennemies.png"},
    {NULL, NULL, T_M_BG, "./img/menu/menu_bg.jpg"},
    {NULL, NULL, T_M2D, "./img/mode_2D.png"},
    {NULL, NULL, T_M3D, "./img/mode_3D.png"},
    {NULL, NULL, T_P_2D, "./img/player_2d.png"},
    {NULL, NULL, T_B_S1, "./img/menu/s1_bouton.png"},
    {NULL, NULL, T_B_S2, "./img/menu/s2_bouton.png"},
    {NULL, NULL, T_B_S3, "./img/menu/s3_bouton.png"},
    {NULL, NULL, T_B_EXIT, "./img/menu/exit.png"},
    {NULL, NULL, T_B_SETTINGS, "./img/menu/settings.png"},
    {NULL, NULL, T_B_BACK, "./img/menu/back_bouton.png"},
    {NULL, NULL, T_ARR_L, "./img/menu/arrow_l.png"},
    {NULL, NULL, T_ARR_R, "./img/menu/arrow_r.png"},
    {NULL, NULL, T_B_HOME, "img/menu/home_bouton.png"},
    {NULL, NULL, T_3D_KNIFE, "./img/weapons/knife_3D.png"},
    {NULL, NULL, T_3D_GUN, "./img/weapons/gun_3D.png"},
    {NULL, NULL, T_3D_SHOTGUN, "./img/weapons/shotgun_3D.png"},
    {NULL, NULL, T_3D_MINIGUN, "./img/weapons/minigun_3D.png"},
    {NULL, NULL, T_2D_KNIFE, "./img/hud/knife_2D.png"},
    {NULL, NULL, T_2D_GUN, "./img/hud/gun_2D.png"},
    {NULL, NULL, T_2D_SHOTGUN, "./img/hud/shotgun_2D.png"},
    {NULL, NULL, T_2D_MINIGUN, "./img/hud/minigun_2D.png"},
    {NULL, NULL, T_HUD, "./img/hud/hud_base.png"},
    {NULL, NULL, T_AMMO, "img/ammo.png"},
    {NULL, NULL, T_LIFE, "img/medic.png"},
    {NULL, NULL, 0, NULL}
};

const size_t SZ_TAB_TEXTURE = sizeof(TAB_TEXTURE) / sizeof(*TAB_TEXTURE);

tab_texture_t *dup_texture(const tab_texture_t texture)
{
    tab_texture_t *new_tab = malloc(sizeof(tab_texture_t));

    if (new_tab == NULL)
        return NULL;
    new_tab->id = texture.id;
    new_tab->file = NULL;
    new_tab->texture = NULL;
    if (texture.id == 0)
        return new_tab;
    new_tab->file = my_strdup(texture.file);
    if (new_tab->file == NULL)
        return free(new_tab), NULL;
    new_tab->texture = sfTexture_createFromFile(new_tab->file, NULL);
    if (!new_tab->texture)
        fprintf(stderr, "failed to load texture:%s\n", new_tab->file);
    new_tab->img = sfTexture_copyToImage(new_tab->texture);
    return new_tab;
}

tab_texture_t **init_textures(void)
{
    tab_texture_t **textures =
            malloc(sizeof(tab_texture_t *) * SZ_TAB_TEXTURE);

    if (textures == NULL)
        return false;
    for (size_t i = 0; i < SZ_TAB_TEXTURE; i++){
        textures[i] = dup_texture(TAB_TEXTURE[i]);
        if (textures[i] == NULL)
            return NULL;
    }
    textures[SZ_TAB_TEXTURE - 1] = NULL;
    return textures;
}
