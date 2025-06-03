/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** my
*/


#ifndef LEVEL_H
    #define LEVEL_H
    # define TILE_SIZE 60
    # define MAP_WIDTH 20
    # define MAP_HEIGHT 20
    # define NB_MAP 3
    #include <stdbool.h>

typedef struct game_handler_s game_handler_t;

/* define 3 map 100 x 100 will be set in config file or
 set in the .h if no cofig file */
typedef struct level_s {
    int actual_level;
    int map[3][MAP_HEIGHT][MAP_WIDTH];
} level_t;
#endif //MAP_H
