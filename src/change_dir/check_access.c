/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** check_access.c
*/

#include "minishell.h"

static int check_access(char **splite_path, char *cmd_name)
{
	int status = 0;
	int alrd_path = 0;

	if (splite_path == NULL || cmd_name == NULL)
		return (-1);
	for (int i = 0 ; splite_path[i] != NULL ; i++) {
		splite_path[i] = add_cmd_to_path(cmd_name, splite_path[i],
			&alrd_path);
		if (splite_path[i] == NULL) {
			status = -2;
			break;
		}
		status = access(splite_path[i], F_OK);
		if (status != -1)
			break;
	}
	if (alrd_path != 1)
		destroy_2darray(splite_path);
	return (status);
}

int check_if_is_cmd(char *env[], char *cmd_name)
{
	char **splite_path = NULL;
	int path_index = find_env(env, "PATH");
	int status = 0;

	if (env == NULL || cmd_name == NULL)
		return (0);
	if (path_index == -1)
		return (manage_cmd_not_found(cmd_name));
	splite_path = splite_path_variable(env[path_index]);
	status = check_access(splite_path, cmd_name);
	if (status == -1)
		manage_cmd_not_found(cmd_name);
	return ((status >= 0) ? 1 : -1);
}

int can_access_to_file(char *filename)
{
	DIR *dir = NULL;

	if (filename == NULL)
		return (0);
	dir = opendir(filename);
	if (dir == NULL && (access(filename, X_OK) != 0)
	&& access(filename, F_OK) == 0) {
		my_puterror(filename);
		my_putstr(": Permission denied.\n");
		return (1);
	} else if (dir == NULL)
		return (0);
	if ((access(filename, W_OK) == -1 || access(filename, R_OK) == -1
	|| access(filename, X_OK) == -1)) {
		my_puterror(filename);
		my_putstr(": Permission denied.\n");
		return (1);
	}
	closedir(dir);
	return (0);
}
