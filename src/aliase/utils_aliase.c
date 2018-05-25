/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_aliase.c
*/

#include "minishell.h"

char *new_str(char *cmd, int size, char *new_cmd)
{
	int i = 0;
	while (cmd[size] != '\0' && cmd[size] != '=') {
		if (cmd[size] == '=')
			size += 1;
		new_cmd[i] = cmd[size];
		i++;
		size++;
	}
	new_cmd[i] = '\0';
	return (new_cmd);
}

int count_equal(char *str)
{
	int equal = 0;
	int i = 0;

	while (str[i] != '\0') {
		if (str[i] == '=')
			equal += 1;
		i++;
	}
	if (equal != 1)
		return (1);
	return (0);
}

int count_str_size(char *str, int i)
{
	int j = 0;

	while (str[i] != '=' && str[i] != '\0') {
		i++;
		j++;
	}
	return (j);
}
