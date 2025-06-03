/*
** EPITECH PROJECT, 2024
** my_put_lnbr
** File description:
** take a longlong unsigned int
*/
#include "my.h"

int my_put_lnbr(unsigned long long int nb)
{
    if (nb <= 9) {
        my_putchar(nb + 48);
    } else {
        my_put_lnbr(nb / 10);
        my_put_lnbr(nb % 10);
    }
    return 0;
}

int my_putnbr(int nb)
{
    if (nb < 0){
        my_putchar('-');
        nb *= -1;
    }
    if (nb <= 9) {
        my_putchar(nb + 48);
    } else {
        my_putnbr(nb / 10);
        my_putnbr(nb % 10);
    }
    return 0;
}
