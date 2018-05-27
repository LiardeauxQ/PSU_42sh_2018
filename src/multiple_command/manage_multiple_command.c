/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_multiple_command.c
*/

#include "minishell.h"

static int check_empty_line(char *cmd)
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

int check_one_separator_command(cmd_t *cmd, shell_t *shell)
{
	int quit = 0;

	if (cmd == NULL)
		return (-1);
	if (cmd->redirection != 0) {
		quit = manage_redirection(cmd, shell, 
		cmd->redirection, NULL);
		return (quit);
	}
	if (cmd->separator == PIPE_SEP)
		quit = manage_pipe(cmd, shell);
	if (cmd->separator == OR_SEP)
		quit = or_condition_cmd(cmd, shell);
	if (cmd->separator == AND_SEP)
		quit = and_condition_cmd(cmd, shell);
	if (cmd->separator == 0)
		quit = check_one_command(cmd, shell);
	return (quit);
}

int analyse_cmd_struct(shell_t *shell)
{
	int quit = 0;

	for (int i = 0 ; shell->cmd[i].separator != -1
	&& shell->cmd[i].cmd != NULL ; i++) {
		quit = check_one_separator_command(&shell->cmd[i], shell);
	}
	return (quit);
}

int manage_multiple_commande(char *str_cmd, shell_t *shell)
{
	int quit = 0;

	if (str_cmd == NULL || check_empty_line(str_cmd) == 0 
	|| shell->env == NULL)
		return (0);
	shell->cmd = create_cmd_struct(str_cmd);
	if (shell->cmd == NULL)
		return (1);
	quit = analyse_cmd_struct(shell);
	quit = print_redirection_error(quit);
	destroy_cmd(shell->cmd);
	return (quit);
}
