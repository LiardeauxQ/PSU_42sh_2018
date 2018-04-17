/*
** EPITECH PROJECT, 2017
** push_swap.c
** File description:
** push_swap main file
*/

#include "my.h"

int my_strtoi(char *number)
{
	int size = my_strlen(number);
	int resultat = 0;
	int negative = 0;
	int i = 0;

	if (number == NULL)
		return (0);
	if (number[0] == '-') {
		negative = 1;
		i = 1;
	}
	while (i < size - 1) {
		resultat = (resultat + number[i] - 48) * 10;
		i = i + 1;
	}
	resultat = resultat + (number[i] - 48);
	if (negative == 1)
		resultat = resultat * (-1);
	return (resultat);
}
