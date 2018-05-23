/*
** EPITECH PROJECT, 2018
** my_str_to_word_array
** File description:
** msh2
*/

#include "manage_multiple_command.h"

int	check_i(char *str, int i, char c)
{
	if (str[i] == c)
		++i;
	return (i);
}

int	check_y(char *str, char c, int y, int i)
{
	if (str[i - 1] != c)
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

	for (int i; str[i] != '\0'; i++) {
		if (str[i] == c && str[i + 1] == '\0')
			break;
		else if (str[i] == c) {
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
	y = check_y(str, c, y, i);
	return (array_null(arr, y));
}

char	**my_str_to_back_tab(char *str, char c)
{
	char	**arr = malloc(sizeof(char * ) * (my_strlen(str) + 1));

	arr[0] = malloc(sizeof(char) * (my_strlen(str) + 1));
	arr = my_str_to_word_array(str, arr, c, 0);
	for (int i = 0; arr[i] != NULL; i++)
		arr[i] = clean(arr[i]);
	return (arr);
}
