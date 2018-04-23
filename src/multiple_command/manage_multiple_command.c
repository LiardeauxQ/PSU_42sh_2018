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

int check_if_redir_error(char ***split_cmd)
{
	int pos = 0;
	int quit = 0;

	if (split_cmd == NULL)
		return (-1);
	while (split_cmd[pos] != NULL) {
		quit = check_redirections_char(split_cmd, pos);
		if (quit == INPUT_REDIR_ERROR)
			return (quit);
		else if (quit == OUTPUT_REDIR_ERROR)
			return (quit);
		pos = pos + 1;
	}
	return (quit);
}

int manage_multiple_commande(char **cmd, char ***env)
{
	char **split_cmd = NULL;
	int error = 0;
	int type = 0;

	if (cmd == NULL || env == NULL)
		return (0);
	if (check_empty_line(*cmd) == 0)
		return (0);
	split_cmd = my_str_to_wordtab(*cmd, " \t");
	if (check_if_special_str(split_cmd, ";") != -1
	|| check_if_special_str(split_cmd, "|") != -1) {
		error = manage_semicolons(*cmd, env);
		if (error < -1)
			return (print_redirection_error(error));
		else
			return (error);
	} else if ((type = check_if_redirection(split_cmd)) != 0)
		return (manage_redirection(*cmd, env, type, NULL));
	else
		return (check_one_command(*cmd, split_cmd, env));
	return (0);
}
