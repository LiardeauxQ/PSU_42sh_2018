/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_path_var.c
*/

#include "minishell.h"

static char **initialize_path_array(char *path_var, int size)
{
	char **splite_path = NULL;
	int way = 0;

	if (path_var == NULL)
		return (NULL);
	for (int i = 0 ; i < size ; i++) {
		if (path_var[i] == ':')
			way = way + 1;
	}
	way = way + 1;
	splite_path = malloc((way + 1) * sizeof(char*));
	check_malloc(splite_path);
	for (int j = 0 ; j < way ; j++) {
		splite_path[j] = malloc(size);
		check_malloc(splite_path[j]);
	}
	return (splite_path);
}

static char *check_end_slash(char *splite_path, int k)
{
	if (splite_path == NULL)
		return (NULL);
	if (splite_path[k - 1] != '/') {
		splite_path[k] = '/';
		k = k + 1;
	}
	splite_path[k] = '\0';
	return (splite_path);
}

char **splite_path_variable(char *path_v)
{
	char **splite_path = NULL;
	int j = 0;
	int k = 0;

	if (path_v == NULL)
		return (NULL);
	splite_path = initialize_path_array(path_v, my_strlen(path_v));
	for (int i = 5 ; i < my_strlen(path_v) ; i++) {
		if (path_v[i] == ':') {
			splite_path[j] = check_end_slash(splite_path[j], k);
			i = i + 1;
			j = j + 1;
			k = 0;
		}
		splite_path[j][k] = path_v[i];
		k = k + 1;
	}
	splite_path[j] = check_end_slash(splite_path[j], k);
	splite_path[j + 1] = NULL;
	return (splite_path);
}
