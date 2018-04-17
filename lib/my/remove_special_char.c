/*
** EPITECH PROJECT, 2017
** libmy
** File description:
** remove_special_char.c
*/

#include "my.h"

char *remove_special_char(char *str, char c)
{
	int find_c = 0;
	int i = 0;

	if (str == NULL)
		return (NULL);
	while (str[i + 1] != '\0') {
		if (str[i] == c)
			find_c = 1;
		if (find_c == 1)
			str[i] = str[i + 1];
		i = i + 1;
	}
	str[i] = '\0';
	for (int j = 0 ; str[j] != '\0' ; j++)
		if (str[j] == c)
			return (remove_special_char(str, c));
	return (str);
}
