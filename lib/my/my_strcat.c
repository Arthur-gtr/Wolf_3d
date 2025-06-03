/*
** EPITECH PROJECT, 2024
** my_strcat
** File description:
** idk
*/
#include "my.h"
#include <stdlib.h>

char *my_strcat(char *dest, char *to_cat)
{
    char *catstr = malloc(sizeof(char) * (my_strlen(to_cat) + my_strlen(dest)
        + 1));
    int parcours = 0;

    if (catstr == NULL)
        return NULL;
    for (int i = 0; dest && dest[i]; i++){
        catstr[parcours] = dest[i];
        parcours++;
    }
    for (int i = 0; to_cat && to_cat[i]; i++){
        catstr[parcours] = to_cat[i];
        parcours++;
    }
    catstr[parcours] = '\0';
    return catstr;
}
