/*
** EPITECH PROJECT, 2024
** Semester_1
** File description:
** my_putsterr
*/
#include <unistd.h>
#include "my.h"

int my_putstrerr(char *str)
{
    write(2, str, my_strlen(str));
    return my_strlen(str);
}
