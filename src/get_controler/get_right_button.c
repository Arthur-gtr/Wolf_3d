/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** get_right_button
*/

#include "call_csfml.h"
#include <stdbool.h>
#include "controller.h"

int check_r2(void)
{
    float r2;

    if (!sfJoystick_isConnected(0))
        return false;
    r2 = sfJoystick_getAxisPosition(0, sfJoystickR);
    if (r2 > 50.0f)
        return true;
    return false;
}

int check_r1(void)
{
    if (!sfJoystick_isConnected(0))
        return false;
    if (sfJoystick_isButtonPressed(0, 5))
        return true;
    return false;
}

int check_r3(void)
{
    if (!sfJoystick_isConnected(0))
        return false;
    if (sfJoystick_isButtonPressed(0, 11)) {
        return true;
    }
    return false;
}

sfUint8 get_right_stick(void)
{
    sfUint8 flag = 0;
    float u = sfJoystick_getAxisPosition(0, sfJoystickU);
    float v = sfJoystick_getAxisPosition(0, sfJoystickV);

    check_triangle();
    if (!sfJoystick_isConnected(0))
        return 0;
    if (u < -50.0f)
        flag |= LEFT;
    if (u > 50.0f)
        flag |= RIGHT;
    if (v < -50.0f)
        flag |= UP;
    if (v > 50.0f)
        flag |= DOWN;
    return flag;
}
