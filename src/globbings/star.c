/*
** EPITECH PROJECT, 2018
** star
** File description:
** 42sh
*/

#include "minishell.h"

char **make_new_array(char **new_array, char *path, char *file, int i)
{
	DIR *dirp = NULL;
	struct dirent *dirent = NULL;

	if ((dirp = opendir(path)) == NULL)
		return (NULL);
	while ((dirent = readdir(dirp)) != NULL) {
		if (match(dirent->d_name, file)) {
			new_array = realloc(new_array, (i + 2)
			* sizeof(char *));
			new_array[i] = malloc(strlen(path) +
			strlen(dirent->d_name) + 1);
			new_array[i] = strcpy(new_array[i], path);
			new_array[i] = strcat(new_array[i],
			dirent->d_name);
			i = i + 1;
		}
	}
	new_array[i] = NULL;
	closedir(dirp);
	return (new_array);
}

char **stock_new_array(char **array, int *i)
{
	int size = count_2d_array(array) + 1;
	char **new_array = malloc((size + 1) * sizeof(char *));

	check_malloc(new_array);
	while (array[*i] && !cinstr(array[*i], '*')) {
		new_array[*i] = strdup(array[*i]);
		*i = *i + 1;
	}
	new_array[*i] = NULL;
	return (new_array);
}

char **trigger_star(char **array)
{
	int i = 0;
	char *path = NULL;
	char *file = NULL;
	char **new_array = stock_new_array(array, &i);

	if (array[i] == NULL) {
		destroy_2darray(new_array);
		return (array);
	}
	file = get_star(array[i]);
	if ((path = find_path(array[i])) == NULL)
		return (NULL);
	new_array = make_new_array(new_array, path, file, i);
	free(path);
	free(file);
	destroy_2darray(array);
	return (new_array);
}
