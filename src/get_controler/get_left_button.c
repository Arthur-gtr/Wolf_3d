/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** get_left_button
*/
#include "call_csfml.h"
#include <stdbool.h>
#include "controller.h"

int check_l2(void)
{
    float l2;

    if (!sfJoystick_isConnected(0))
        return false;
    l2 = sfJoystick_getAxisPosition(0, sfJoystickZ);
    if (l2 > 50.0f)
        return true;
    return false;
}

int check_l1(void)
{
    if (!sfJoystick_isConnected(0))
        return false;
    if (sfJoystick_isButtonPressed(0, 4))
        return true;
    return false;
}

int check_l3(void)
{
    if (!sfJoystick_isConnected(0))
        return false;
    if (sfJoystick_isButtonPressed(0, 10))
        return true;
    return false;
}

sfUint8 get_left_stick(void)
{
    sfUint8 flag = 0;
    float x = 0;
    float y = 0;

    if (!sfJoystick_isConnected(0))
        return 0;
    x = sfJoystick_getAxisPosition(0, sfJoystickX);
    y = sfJoystick_getAxisPosition(0, sfJoystickY);
    if (x < -50.0f)
        flag |= LEFT;
    if (x > 50.0f)
        flag |= RIGHT;
    if (y < -50.0f)
        flag |= UP;
    if (y > 50.0f)
        flag |= DOWN;
    return flag;
}
