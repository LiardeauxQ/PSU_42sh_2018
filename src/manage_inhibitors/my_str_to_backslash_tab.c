/*
** EPITECH PROJECT, 2017
** lib
** File description:
** my_str_to_wordtab.c
*/

#include "manage_multiple_command.h"

int check_same_char(char str, char *c)
{
	for (int i = 0; c[i] != '\0'; i++)
		if (c[i] == str || c[i] == '\\')
			return (1);
	return (0);
}

static int check_multiple_char(char *str, char *c, int i)
{
	while (str[i] != '\0' && (check_same_char(str[i], c) == 1))
		++i;
	return (i);
}

int count_rec(char *str, char *c)
{
	int size = 1;

	for (int i = 0; i < my_strlen(str); i++) {
		if (check_same_char(str[i], c) == 1)
			++size;
		i = check_multiple_char(str, c, i);
	}
	return (size);
}

static char **initialize_str_to_tab_array(char *str, char *c)
{
	int size = count_rec(str, c);
	char **array = malloc(sizeof(char *) * (size + 1));

	check_malloc(array);
	for (int i = 0; i < size; i++) {
		array[i] = malloc(my_strlen(str) + 1);
		check_malloc(array[i]);
	}
	return (array);
}

char **my_str_to_backslash_tab(char *str, char *c)
{
	char **tab_str = NULL;
	int j = 0;
	int k = 0;

	if (str == NULL || c == NULL || my_strlen(str) == 0)
		return (NULL);
	tab_str = initialize_str_to_tab_array(str, c);
	j = check_multiple_char(str, c, 0);
	for (int a = 0; j < my_strlen(str); a++) {
		tab_str[k][a] = str[j];
		++j;
		if (str[j] == '\0' || (check_same_char(str[j], c) == 1)) {
			j = check_multiple_char(str, c, j);
			tab_str[k][a] = '\0';
			a = 0;
			++k;
		}
	}
	tab_str[k] = NULL;
	return (tab_str);
}
