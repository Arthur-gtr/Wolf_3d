/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** int_to_str
*/
#include "my.h"
#include <stdlib.h>

char *int_to_str(int nb)
{
    char *str_int = malloc(sizeof(char) * (1 + my_nbrlen(nb)));
    int in_str = 0;

    if (nb < 0){
        nb *= -1;
        str_int[0] = '-';
        in_str += 1;
    }
    for (; nb > 0; in_str += 1){
        str_int[in_str] = nb % 10 + 48;
        nb /= 10;
    }
    str_int[in_str] = '\0';
    my_revstr(str_int);
    return str_int;
}
