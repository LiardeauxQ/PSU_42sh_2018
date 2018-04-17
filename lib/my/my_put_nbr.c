/*
** EPITECH PROJECT, 2017
** my_put_nbr
** File description:
** display a number
*/

#include "my.h"

int my_put_nbr(int n)
{
	int reste = 0;

	if (n < 0) {
		n = (-1) * n;
		my_putchar('-');
	}
	reste = n % 10;
	while (n >= 10) {
		n = my_put_nbr((n - reste) / 10);
	}
	my_putchar(reste + 48);
	return (n);
}
