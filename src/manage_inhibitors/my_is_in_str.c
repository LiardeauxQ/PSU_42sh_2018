/*
** EPITECH PROJECT, 2018
** my_is_in_str.c
** File description:
** my_is_in_str.c
*/

#include "manage_multiple_command.h"

int	my_is_in_str(char *str, char c)
{
	for (int i = 0; str[i] != '\0'; i++)
		if (str[i] == c)
			return (1);
	return (0);
}
