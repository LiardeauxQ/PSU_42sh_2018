/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_path_var.c
*/

#include "minishell.h"

static char *add_end_slash(char *split_path, int k)
{
	if (split_path == NULL)
		return (NULL);
	if (split_path[k - 1] != '/') {
		split_path[k] = '/';
		k = k + 1;
	}
	split_path[k] = '\0';
	return (split_path);
}

char **split_path_var(char *path_v, char *c)
{
	char **split_path = my_str_to_wordtab(path_v, c);
	int str_size = 0;

	if (split_path == NULL)
		return (NULL);
	for (int i = 0 ; split_path[i] != NULL ; i++) {
		str_size = my_strlen(split_path[i]);
		split_path[i] = add_end_slash(split_path[i], str_size);
	}
	free(path_v);
	return (split_path);
}
