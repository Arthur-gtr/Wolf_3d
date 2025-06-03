/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** dup_list
*/
#include "my.h"

list_t *dup_list(list_t *list)
{
    list_t *cp_list = list_create();

    if (list == NULL || cp_list == NULL)
        return cp_list;
    for (node_t *cur = list->head; cur; cur = cur->next)
        push_back(cp_list, cur->data);
    return cp_list;
}
