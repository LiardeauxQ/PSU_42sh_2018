/*
** EPITECH PROJECT, 2017
** libmy
** File description:
** my_int_tostr.c
*/

#include "my.h"

int length_nbr(int n)
{
	int i = 0;
	int reste = 0;

	if (n < 0) {
		n = n * (-1);
		i = i + 1;
	}
	while (n >= 10) {
		reste = n % 10;
		n = (n - reste) / 10;
		i = i + 1;
	}
	return (i + 2);
}

char *int_tostr(int n)
{
	int reste = 0;
	int i = 0;
	char *new_str;

	new_str = malloc((length_nbr(n)) * sizeof(char*));
	while (n >= 10) {
		reste = n % 10;
		n = (n - reste) / 10;
		new_str[i] = reste + 48;
		i = i + 1;
	}
	new_str[i] = n + 48;
	new_str[i + 1] = '\0';
	return (my_revstr(new_str));
}
