/*
** EPITECH PROJECT, 2018
** trim_spaces
** File description:
** libfunc
*/

#include "manage_multiple_command.h"

char *clean(char *str)
{
	char *new_str = malloc(my_strlen(str) + 1);
	int j = 0;

	for (int i = 0 ; str[i] != '\0' ; i++) {
		if (str[i] != ' ' && str[i] != '\t') {
			if (str[i] == '\\')
				i = i + 1;
			new_str[j] = str[i];
			j = j + 1;
		}
	}
	new_str[j] = '\0';
	return (new_str);
}
