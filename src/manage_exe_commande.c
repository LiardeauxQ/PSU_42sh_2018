/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_exe_commande.c
*/

#include "minishell.h"

int check_already_path(char *pathname)
{
	if (pathname == NULL)
		return (-1);
	for (int i = 0 ; pathname[i] != '\0' ; i++) {
		if (pathname[i] == '/')
			return (1);
	}
	return (0);
}

char *add_cmd_to_path(char *cmd_name, char *split_path, int *alrd_path)
{
	int status = check_already_path(cmd_name);

	if (cmd_name == NULL || split_path == NULL || alrd_path == NULL)
		return (NULL);
	if (status == 1) {
		if (can_access_to_file(cmd_name))
			return (NULL);
		split_path = cmd_name;
		*alrd_path = 1;
	} else if (status == 0)
		split_path = my_strcat(split_path, cmd_name);
	else
		return (NULL);
	return (split_path);
}

int exe_cmd(char *split_path, char **arg, char *env[], int *alrd_path)
{
	int status = 0;

	if (split_path == NULL || arg == NULL || env == NULL
		|| alrd_path == NULL)
		return (-1);
	split_path = add_cmd_to_path(arg[0], split_path, alrd_path);
	if (split_path == NULL)
		return (-2);
	status = execve(split_path, arg, env);
	return (status);
}

int manage_executable(char *env[], char **arg)
{
	char **split_path = NULL;
	int child_pid = -1;
	int alrd_path = 0;
	int status = 0;

	if ((split_path = split_path_variable(find_env_var_value(env, "PATH"),
	":")) == NULL)
		return (child_pid);
	child_pid = fork();
	if (child_pid == -1) {
		my_puterror("Error with fork()\n");
		exit(84);
	} else if (child_pid != 0)
		return (child_pid);
	for (int i = 0 ; split_path[i] != NULL ; i++) {
		status = exe_cmd(split_path[i], arg, env, &alrd_path);
		if (status != -1)
			break;
	}
	destroy_2darray(split_path);
	return (child_pid);
}
