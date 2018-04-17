/*
** EPITECH PROJECT, 2017
** my_putstr
** File description:
** display a string
*/

#include "my.h"

int my_putstr(char const *str)
{
	if (str == NULL)
		return (1);
	write(1, str, my_strlen(str));
	return (0);
}
