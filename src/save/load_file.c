/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** load_file
*/

#include "game.h"

bool load_from_file(game_handler_t *g_h, char *file, void *to_rd, ssize_t sz)
{
    FILE *fd = NULL;
    char path[256];
    ssize_t count_rd = 0;

    snprintf(path, sizeof(path), "%s%s", g_h->game->actual_save, file);
    fd = fopen(path, "rb");
    if (fd == NULL)
        return false;
    count_rd = fread(to_rd, sz, 1, fd);
    fclose(fd);
    if (count_rd != 1)
        return false;
    return true;
}
