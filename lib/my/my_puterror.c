/*
** EPITECH PROJECT, 2017
** my_puterror.c
** File description:
** display in error output
*/

#include "my.h"

int my_puterror(char const *str)
{
	if (str == NULL)
		return (1);
	write(2, str, my_strlen(str));
	return (0);
}
