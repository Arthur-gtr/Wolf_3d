/*
** EPITECH PROJECT, 2024
** my_str_isnum
** File description:
** idk
*/

#include "ctype.h"

int my_str_isnum(char const *str)
{
    for (; *str != '\0'; str++) {
        if (!isdigit(*str))
            return 1;
    }
    return 0;
}
