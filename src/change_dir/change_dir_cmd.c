/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** change_dir_cmd.c
*/

#include "minishell.h"

char *find_env_var_value(char *env[], char *env_var)
{
	char *var_value = NULL;
	int var_index = find_env(env, env_var);
	int i = 0;
	int k = 0;

	if (env == NULL || env_var == NULL || var_index == -1)
		return (NULL);
	while (env[var_index][i] != '\0' && env[var_index][i] != '=')
		i = i + 1;
	var_value = malloc(my_strlen(env[var_index]) + 1);
	check_malloc(var_value);
	for (int j = i + 1 ; j < my_strlen(env[var_index]) ; j++) {
		var_value[k] = env[var_index][j];
		k = k + 1;
	}
	var_value[k] = '\0';
	return (var_value);
}

static int manage_cd_commande_option(char ***env, char *new_dir,
	char current_dir[])
{
	if (env == NULL || new_dir == NULL)
		return (-1);
	if (new_dir[0] == '-' && my_strlen(new_dir) == 1)
		*env = update_oldpwd_var(*env, current_dir);
	else {
		if (chdir(new_dir) == -1) {
			my_puterror(new_dir);
			my_puterror(": Not a directory.\n");
			free(new_dir);
			return (1);
		}
		*env = update_pwd_var(*env, current_dir);
	}
	free(new_dir);
	return (0);
}

int change_dir_cmd(char ***env, char **argv)
{
	char *new_dir = NULL;
	char current_dir[500];

	if (env == NULL || argv == NULL)
		return (-1);
	if (check_cd_error(argv[1], count_2d_array(argv)))
		return (1);
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		return (0);
	if (argv[1] == NULL)
		new_dir = find_env_var_value(*env, "HOME");
	else
		new_dir = my_strdup(argv[1]);
	return (manage_cd_commande_option(env, new_dir, current_dir));
}
