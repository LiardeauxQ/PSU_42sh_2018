/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_pwd_var.c
*/

#include "minishell.h"

static char **check_empty_pwd_var(char **env, int *pwd_index,
	int *oldpwd_index)
{
	int size_env = count_2d_array(env);

	if (env == NULL || pwd_index == NULL || oldpwd_index == NULL)
		return (NULL);
	if (*pwd_index == -1) {
		*pwd_index = size_env;
		if (*oldpwd_index == -1) {
			*oldpwd_index = size_env + 1;
			env[*oldpwd_index + 1] = NULL;
		} else
			env[*pwd_index + 1] = NULL;
	} else if (*oldpwd_index == -1) {
		*oldpwd_index = size_env;
		env[*oldpwd_index + 1] = NULL;
	}
	return (env);
}

char **update_pwd_var(char *env[], char current_dir[])
{
	int pwd_index = 0;
	int oldpwd_index = 0;
	char pwd_value[500];

	pwd_index = find_env(env, "PWD");
	oldpwd_index = find_env(env, "OLDPWD");
	if (getcwd(pwd_value, sizeof(pwd_value)) == NULL)
		return (env);
	env = check_empty_pwd_var(env, &pwd_index, &oldpwd_index);
	env[pwd_index] = update_var_env("PWD", pwd_value);
	env[oldpwd_index] = update_var_env("OLDPWD", current_dir);
	return (env);
}

char **update_oldpwd_var(char *env[], char current_dir[])
{
	char *oldpwd_path = NULL;
	char *oldpwd_var_name = "OLDPWD";
	int oldpwd_index = find_env(env, oldpwd_var_name);
	int pwd_index = find_env(env, "PWD");

	if (oldpwd_index == -1) {
		my_puterror(": invalid directorie\n");
		return (env);
	} else if (pwd_index == -1)
		pwd_index = count_2d_array(env);
	oldpwd_path = find_env_var_value(env, oldpwd_var_name);
	env[pwd_index] = update_var_env("PWD", oldpwd_path);
	env[oldpwd_index] = update_var_env(oldpwd_var_name, current_dir);
	if (chdir(oldpwd_path) == -1) {
		my_puterror("chdir : invalid directorie\n");
		return (env);
	}
	return (env);
}
