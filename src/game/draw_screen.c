/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** draw_screen
*/

#include "game.h"
#include "ray_casting.h"

static
node_t *sort_by_dist(node_t *left, node_t *right)
{
    node_t *result = NULL;
    entities_t *left_d = NULL;
    entities_t *right_d = NULL;

    if (!left)
        return right;
    if (!right)
        return left;
    left_d = (entities_t *)(left->data);
    right_d = (entities_t *)(right->data);
    if (left_d->distance > right_d->distance) {
        result = left;
        result->next = sort_by_dist(left->next, right);
    } else {
        result = right;
        result->next = sort_by_dist(left, right->next);
    }
    return result;
}

static
node_t *get_pivot(node_t *head)
{
    node_t *slow = head;
    node_t *fast = head->next;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

static
node_t *quick_sort(node_t *head)
{
    node_t *pivot = NULL;
    node_t *next_half = NULL;
    node_t *left = NULL;
    node_t *right = NULL;

    if (head == NULL || head->next == NULL)
        return head;
    pivot = get_pivot(head);
    next_half = pivot->next;
    pivot->next = NULL;
    left = quick_sort(head);
    right = quick_sort(next_half);
    return sort_by_dist(left, right);
}

static
float find_dist(float x1, float y1, float x2, float y2)
{
    return ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

static
void fill_distance(node_t *node, entities_t *player)
{
    entities_t *ent = NULL;

    if (node == NULL)
        return;
    ent = (entities_t *)node->data;
    ent->distance = find_dist(ent->coord.x, ent->coord.y,
        player->coord.x, player->coord.y);
    return fill_distance(node->next, player);
}

/*CALL all the function to draw*/
void draw_screen(game_handler_t *game)
{
    fill_distance(game->game->ent->entities->head,
        game->game->ent->player->property);
    game->game->ent->entities->head =
        quick_sort(game->game->ent->entities->head);
    draw_wall(&game->ray_cast, game->screen->win);
    draw_sprite(game, game->screen->win);
    draw_hud(game->game->hud, game);
}
