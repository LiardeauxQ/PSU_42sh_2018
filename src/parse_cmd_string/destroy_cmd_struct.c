/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** destroy_cmd_struct.c
*/

#include "minishell.h"

static void destroy_cmd_child(cmd_t *cmd)
{
	if (cmd == NULL)
		return;
	for (int i = 0 ; cmd[i].separator != -1 ; i++) {
		destroy_cmd(cmd[i].childs);
		if (cmd[i].cmd)
			free(cmd[i].cmd);
		if (cmd[i].argv)
			destroy_2darray(cmd[i].argv);
		if (cmd[i].childs)
			free(cmd[i].childs);
	}
}

void destroy_cmd(cmd_t *cmd)
{
	if (cmd == NULL)
		return;
	destroy_cmd_child(cmd);
	free(cmd);
}
