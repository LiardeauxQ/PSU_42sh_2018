/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** unset_env_commande.c
*/

#include "minishell.h"

static char **delete_env_var(char *env[], char **argv, int i)
{
	int size = count_2d_array(env);
	int current_var = 0;

	if (my_strcmp(argv[i], "*")) {
		for (int j = 0 ; j < size ; j++)
			env[j] = NULL;
	}
	if ((current_var = find_env(env, argv[i])) != -1) {
		for (int j = current_var ; j < size ; j++)
			env[j] = env[j + 1];
	}
	return (env);
}

int unset_env_commande(char ***env, char **argv)
{
	int i = 1;

	if (env == NULL || argv == NULL)
		return (-1);
	while (argv[i] != NULL) {
		*env = delete_env_var(*env, argv, i);
		i = i + 1;
	}
	return (0);
}
