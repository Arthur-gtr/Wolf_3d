/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** destroy_list
*/
#include "my.h"
#include <stdlib.h>

void destroy_list(list_t *list)
{
    node_t *next = NULL;

    if (list == NULL)
        return;
    for (node_t *cur = list->head; cur; cur = next){
        next = cur->next;
        destroy_nodes(list, cur);
    }
    if (list != NULL)
        free(list);
    list = NULL;
}
