/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_error.c
*/

#include "minishell.h"

int manage_cmd_not_found(char *cmd_name)
{
	if (cmd_name == NULL)
		return (0);
	my_puterror(cmd_name);
	my_puterror(": Command not found.\n");
	return (-1);
}

int print_redirection_error(int error)
{
	if (error == INPUT_REDIR_ERROR) {
		my_puterror("Ambiguous input redirect.\n");
		return (1);
	} else if (error == OUTPUT_REDIR_ERROR) {
		my_puterror("Ambiguous output redirect.\n");
		return (1);
	}
	return (0);
}

int check_cd_error(char *directory, int cmd_size)
{
	int is_dir = access(directory, F_OK);
	int read_dir = access(directory, R_OK);

	if (directory == NULL)
		return (0);
	if (directory[0] == '-' && my_strlen(directory) == 1)
		return (0);
	if (cmd_size > 2) {
		my_puterror("cd : too many arguments.\n");
		return (1);
	}
	if (is_dir == -1 || read_dir == -1) {
		my_puterror(directory);
		if (is_dir == -1)
			my_puterror(": No such file or directory.\n");
		else
			my_puterror(": Permisson denied.\n");
		return (1);
	}
	return (0);
}
