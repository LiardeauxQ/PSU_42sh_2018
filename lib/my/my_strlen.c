/*
** EPITECH PROJECT, 2017
** my_strlen
** File description:
** count the length of the string
*/

#include "my.h"

int my_strlen(char const *str)
{
	int i = 0;

	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
		i = i + 1;
	return (i);
}
