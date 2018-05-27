/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** condition_command.c
*/

#include "minishell.h"

int and_condition_cmd(cmd_t *cmd, shell_t *shell)
{
	int quit = 0;

	for (int i = 0 ; cmd->childs[i].separator != -1 ; i++) {
		cmd->childs[i].exit_status =
		check_one_separator_command(&cmd->childs[i], shell);
		quit = cmd->childs[i].exit_status;
		if (cmd->childs[i].exit_status != 0)
			break;
	}
	return (quit);
}

int or_condition_cmd(cmd_t *cmd, shell_t *shell)
{
	int j = 0;
	int quit = 0;

	for (int i = 0 ; cmd->childs[i].separator != -1 ; i++)
		cmd->childs[i].exit_status =
		check_one_separator_command(&cmd->childs[i], shell);
	while (cmd->childs[j].separator != -1) {
		if (cmd->childs[j].exit_status == 0)
			return (0);
		quit = cmd->childs[j].exit_status;
		j = j + 1;
	}
	return (quit);
}