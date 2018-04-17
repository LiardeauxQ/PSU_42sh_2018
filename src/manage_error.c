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

int check_cd_error(char **argv)
{
	int size = count_2d_array(argv);
	int is_dir = access(argv[1], F_OK);
	int read_dir = access(argv[1], R_OK);

	if (argv[1][0] == '-' && my_strlen(argv[1]) == 1)
		return (0);
	if (size > 2) {
		my_puterror("cd : too many arguments.\n");
		return (1);
	}
	if (is_dir == -1) {
		my_puterror(argv[1]);
		my_puterror(": No such file or directory.\n");
		return (1);
	} else if (read_dir == -1) {
		my_puterror(argv[1]);
		my_puterror(": Permisson denied.\n");
		return (1);
	}
	return (0);
}
