/*
** EPITECH PROJECT, 2018
** star
** File description:
** 42sh
*/

#include "minishell.h"

int match(char *str, char *s)
{
	char *tmp_str = strdup(str);
	char *tmp_s = strdup(s);

	for (int i = 0 ; str[i] != '\0' && s[i] != '*' ; i++) {
		if (str[i] != s[i])
			return (0);
	}
	tmp_str = my_revstr(tmp_str);
	tmp_s = my_revstr(tmp_s);
	for (int i = 0 ; tmp_str[i] != '\0' && tmp_s[i] != '*' ; i++) {
		if (tmp_str[i] != tmp_s[i])
			return (0);
	}
	free(tmp_str);
	free(tmp_s);
	return (1);
}

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
	path = malloc((my_strlen(str) + 1) * sizeof(char));
	check_malloc(path);
	for (int j = 0 ; j < path_pos ; j++)
		path[j] = str[k++];
	path[path_pos] = '\0';
	return (path);
}

char **make_new_array(char **new_array, char *path, char *file)
{
	int size = count_2d_array(new_array) - 1;
	DIR *dirp = NULL;
	struct dirent *dirent = NULL;

	if ((dirp = opendir(path)) == NULL)
		return (NULL);
	while ((dirent = readdir(dirp)) != NULL) {
		if (match(dirent->d_name, file)) {
			new_array = realloc(new_array, (size + 2)
			* sizeof(char *));
			new_array[size - 1] = my_strdup(dirent->d_name);
			size = size + 1;
		}
	}
	new_array[size - 1] = NULL;
	closedir(dirp);
	return (new_array);
}

char **trigger_star(char **array)
{
	int size = count_2d_array(array) + 1;
	int i = 0;
	char *path = NULL;
	char *file = NULL;
	char **new_array = NULL;

	new_array = malloc((size + 1) * sizeof(char *));
	while (!cinstr(array[i], '*')) {
		new_array[i] = strdup(array[i]);
		i = i + 1;
	}
	file = get_star(array[i]);
	new_array[i] = NULL;
	if ((path = find_path(array[i])) == NULL)
		return (NULL);
	new_array = make_new_array(new_array, path, file);
	free(path);
	free(file);
	return (new_array);
}