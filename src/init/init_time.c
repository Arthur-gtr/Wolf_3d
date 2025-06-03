/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** init_player_ennemies
*/
#include "game.h"
#include "entities.h"

bool need_refresh_clock(time_management_t *sound_clock, float sec_reset)
{
    sound_clock->time = sfClock_getElapsedTime(sound_clock->clock);
    sound_clock->time_as_second = sfTime_asSeconds(sound_clock->time);
    if (sound_clock->time_as_second > sec_reset){
        sfClock_restart(sound_clock->clock);
        return true;
    }
    return false;
}

time_management_t init_clock(void)
{
    time_management_t time = {
        .clock = sfClock_create(),
        .time = {0},
        .time_as_micro_second = 0,
        .time_as_second = 0};

    return time;
}
