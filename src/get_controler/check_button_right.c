/*
** EPITECH PROJECT, 2025
** G-ING-210-REN-2-1-wolf3d-clovis.nedelec
** File description:
** check_button_right
*/

#include "call_csfml.h"
#include <stdbool.h>
#include "controller.h"

int check_cross(void)
{
    if (!sfJoystick_isConnected(0))
        return false;
    if (sfJoystick_isButtonPressed(0, 0)) {
        return true;
    }
    return false;
}

int check_circle(void)
{
    if (!sfJoystick_isConnected(0))
        return false;
    if (sfJoystick_isButtonPressed(0, 1))
        return true;
    return false;
}

int check_square(void)
{
    if (!sfJoystick_isConnected(0))
        return false;
    if (sfJoystick_isButtonPressed(0, 2))
        return true;
    return false;
}

int check_triangle(void)
{
    if (!sfJoystick_isConnected(0))
        return false;
    if (sfJoystick_isButtonPressed(0, 3))
        return true;
    return false;
}
