/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_environment.c
*/

#include "minishell.h"

static int compare_env_var(char const *env, char const *var_to_search)
{
	int size = my_strlen(var_to_search);
	int match = 0;
	int i = 0;

	if (env == NULL || var_to_search == NULL)
		return (-1);
	while (env[i] != '=') {
		if (env[i] != var_to_search[i]) {
			match = 0;
			break;
		} else
			match = 1;
		i = i + 1;
	}
	if (i != size)
		match = 0;
	return (match);
}

int find_env(char *env[], char const *var_to_search)
{
	int match = 0;

	if (env == NULL || var_to_search == NULL)
		return (-1);
	for (int i = 0 ; env[i] != NULL ; i++) {
		match = compare_env_var(env[i], var_to_search);
		if (match == 1)
			return (i);
	}
	return (-1);
}

void display_env_var(char *env[])
{
	int i = 0;

	if (env == NULL)
		return;
	while (env[i] != NULL) {
		my_putstr(env[i]);
		my_putchar('\n');
		i = i + 1;
	}
}

char *create_var_env(char **argv, int size_cmd)
{
	char *new_var = NULL;
	int k = 0;
	int i = 0;

	if (argv == NULL)
		return (NULL);
	new_var = malloc(size_cmd + 1);
	check_malloc(new_var);
	for (i = 1 ; argv[i] != NULL ; i++) {
		for (int j = 0 ; argv[i][j] != '\0' ; j++) {
			new_var[k] = argv[i][j];
			k = k + 1;
		}
		if (i == 1)
			new_var[k] = '=';
		k = k + 1;
	}
	if (i == 3)
		k = k - 1;
	new_var[k] = '\0';
	return (new_var);
}

char *update_var_env(char *var_name, char *var_value)
{
	char *var = NULL;
	int i = 0;

	if (var_name == NULL || var_value == NULL)
		return (NULL);
	var = malloc(my_strlen(var_value) + my_strlen(var_name) + 2);
	check_malloc(var);
	while (i < my_strlen(var_name)) {
		var[i] = var_name[i];
		i = i + 1;
	}
	var[i] = '=';
	i = i + 1;
	for (int j = 0 ; j < my_strlen(var_value) ; j++) {
		var[i] = var_value[j];
		i = i + 1;
	}
	var[i] = '\0';
	return (var);
}
