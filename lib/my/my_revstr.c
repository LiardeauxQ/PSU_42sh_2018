/*
** EPITECH PROJECT, 2017
** my_revstr.c
** File description:
** reverse a string
*/

#include "my.h"

char *my_revstr(char *str)
{
	int i = 0;
	int j = 0;
	char str_temp = 0;

	if (my_strlen(str) == 0)
		return (NULL);
	else if (my_strlen(str) < 1)
		return (str);
	while (str[i] != '\0') {
		i = i + 1;
	}
	i = i - 1;
	while (i > j) {
		str_temp = str[j];
		str[j] = str[i];
		str[i] = str_temp;
		j = j + 1;
		i = i - 1;
	}
	return (str);
}
