/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** tab_completion.c
*/

#include "minishell.h"

int find_cmd_completion(char *cmd, int cursor)
{
	char *tmp = malloc((cursor + 1) * sizeof(char));

	for (int i = 0 ; i < cursor ; i++)
		tmp[i] = cmd[i];
	tmp[cursor + 1] = '\0';
}