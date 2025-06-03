/*
** EPITECH PROJECT, 2024
** my_str_isalpha
** File description:
** idk
*/

#include "ctype.h"

int my_str_isalpha(char const *str)
{
    for (; *str != '\0'; str++) {
        if (!isalnum(*str))
            return 1;
    }
    return 0;
}
