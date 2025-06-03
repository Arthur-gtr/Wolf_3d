/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** save_value
*/

#include "game.h"

static
bool init_folder(game_handler_t *game)
{
    if (access("./save_f", F_OK) < 0)
        if (mkdir("./save_f", 0755) < 0)
            perror("mkdir fail:");
    if (access(game->game->actual_save, F_OK) < 0)
        if (mkdir(game->game->actual_save, 0755) < 0)
            perror("mkdir fail:");
    return true;
}

bool save_to_file(game_handler_t *g_h, char *file, void *to_rd, ssize_t sz)
{
    FILE *fd = NULL;
    ssize_t count_wr = 0;
    char path[256];

    if (!init_folder(g_h))
        return false;
    snprintf(path, sizeof(path), "%s%s", g_h->game->actual_save, file);
    fd = fopen(path, "wb");
    if (fd == NULL)
        return false;
    count_wr = fwrite(to_rd, sz, 1, fd);
    fclose(fd);
    if (count_wr < 1)
        return false;
    return true;
}
