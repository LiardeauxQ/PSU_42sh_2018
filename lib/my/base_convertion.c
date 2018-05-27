/*
** EPITECH PROJECT, 2017
** libmy
** File description:
** base_convertion.c
*/

#include "my.h"

int my_pow(int nb, int pow_nbr)
{
	int i = 1;
	int number = nb;

	if (pow_nbr == 0)
		return (1);
	while (i < pow_nbr) {
		number = number * nb;
		i = i + 1;
	}
	return (number);
}

int convert_base_to_decimal(char *nb, int base)
{
	int result = 0;
	int rest = 0;
	int j = 0;
	int hexa = 0;

	if (nb[0] == 'x')
		hexa = 1;
	for (int i = my_strlen(nb) - 1 ; i >= hexa ; i--) {
		if (nb[i] >= 'A' && nb[i] <= 'F')
			rest = 10 + nb[i] - 65;
		else
			rest = nb[i] - 48;
		result += rest * my_pow(base, j);
		j = j + 1;
	}
	return (result);
}
