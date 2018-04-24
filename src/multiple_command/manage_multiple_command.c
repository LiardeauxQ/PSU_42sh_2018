/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_multiple_command.c
*/

#include "minishell.h"

int check_empty_line(char *cmd)
{
	int i = 0;
	int size = 0;

	if (cmd == NULL)
		return (0);
	while (i < my_strlen(cmd)) {
		if (cmd[i] != ' ' && cmd[i] != '\t')
			size = size + 1;
		i = i + 1;
	}
	return (size);
}

int check_if_redir_error(cmd_t *cmd)
{
	int pos = 0;
	int quit = 0;

	if (cmd == NULL)
		return (-1);
	while (cmd[pos].separator != -1) {
		quit = check_redirections_char(cmd, pos);
		if (quit == INPUT_REDIR_ERROR)
			return (quit);
		else if (quit == OUTPUT_REDIR_ERROR)
			return (quit);
		pos = pos + 1;
	}
	return (quit);
}

int analyse_cmd_struct(cmd_t *cmd, char ***env)
{
	int quit = 0;

	for (int i = 0 ; cmd[i].separator != -1 ; i++) {
		if (cmd[i].redirection != 0) {
			quit = manage_redirection(&cmd[i], env,
				cmd[i].redirection, NULL);
			continue;
		}
		if (cmd[i].separator == PIPE_SEP)
			quit = manage_pipe(&cmd[i], env);
		if (cmd[i].separator == OR_SEP);
		if (cmd[i].separator == AND_SEP);
		if (cmd[i].separator == 0)
			quit = check_one_command(&cmd[i], env);
	}
	return (quit);
}

int manage_multiple_commande(char *str_cmd, char ***env)
{
	cmd_t *cmd = NULL;
	int quit = 0;

	if (str_cmd == NULL || check_empty_line(str_cmd) == 0 || env == NULL)
		return (0);
	cmd = create_cmd_struct(str_cmd);
	quit = analyse_cmd_struct(cmd, env);
	quit = print_redirection_error(quit);
	destroy_cmd(cmd);
	return (quit);
}
