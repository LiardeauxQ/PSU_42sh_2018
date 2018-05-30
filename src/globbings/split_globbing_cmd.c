/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** split_globbing_cmd.c
*/

#include "minishell.h"

int find_path_pos(char *str)
{
	int path_pos = 0;

	for (int i = my_strlen(str) - 1 ; i >= 0 ; i--) {
		if (str[i] == '/')
			break;
		path_pos = i;
	}
	return (path_pos);
}

char *get_star(char *str)
{
	int k = 0;
	int path_pos = 0;
	char *file = NULL;

	path_pos = find_path_pos(str);
	file = malloc((my_strlen(str) + 1) * sizeof(char));
	check_malloc(file);
	for (int j = path_pos ; j < my_strlen(str) ; j++)
		file[k++] = str[j];
	file[k] = '\0';
	return (file);
}

char *find_path(char *str)
{
	int k = 0;
	int path_pos = 0;
	char *path = NULL;

	path_pos = find_path_pos(str);
	if (path_pos == 0)
		return (strdup("./"));
	path = malloc((my_strlen(str) + 1) * sizeof(char));
	check_malloc(path);
	for (int j = 0 ; j < path_pos ; j++)
		path[j] = str[k++];
	path[path_pos] = '\0';
	return (path);
}