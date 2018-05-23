/*
** EPITECH PROJECT, 2018
** my_str_to_word_array
** File description:
** msh2
*/

#include "manage_multiple_command.h"

int	check_i(char *str, int i, char c)
{
	if (str[i] == c && str[i - 1] != '\\')
		++i;
	return (i);
}

int	check_y(char *str, char c, int y, int i)
{
	if (str[i] != c)
		++y;
	return (y);
}

char	**array_null(char **arr, int y)
{
	arr[y] = NULL;
	return (arr);
}

char	**my_str_to_word_array(char *str, char **arr, char c, int i)
{
	int	x = 0;
	int	y = 0;

	for (; str[i] != '\0'; i++) {
		if (str[i] == c && str[i + 1] == '\0')
			break;
		else if (str[i] == c && str[i - 1] != '\\') {
			arr[y][x] = '\0';
			++i;
			++y;
			x = 0;
			arr[y] = malloc(sizeof(char) * (my_strlen(str) + 1));
		}
		i = check_i(str, i, c);
		arr[y][x] = str[i];
		++x;
	}
	arr[y][x] = '\0';
	y = check_y(str, c, y, i - 1);
	return (array_null(arr, y));
}

char	**my_str_to_back_tab(char **tab, char *str, char c)
{
	if (tab == NULL) {
		tab = malloc(sizeof(char * ) * (my_strlen(str) + 1));
		tab[0] = malloc(sizeof(char) * (my_strlen(str) + 1));
		tab[1] = NULL;
	}
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == c) {
			tab = my_str_to_word_array(str, tab, c, 0);
			break;
		} else if (str[i + 1] == '\0') {
			my_free_tab(tab);
			return (NULL);
		}
	}
	for (int i = 0; tab[i] != NULL; i++)
		tab[i] = clean(tab[i]);
	return (tab);
}
