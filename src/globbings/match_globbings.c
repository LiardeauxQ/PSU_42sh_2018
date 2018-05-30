/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** match_globbings.c
*/

#include "minishell.h"

static int find_globbings_size(char *str)
{
	int size = 0;

	for (int i = 0 ; str[i] != '\0' && str[i] != '*' ; i++)
		size = size + 1;
	return (size);
}

int match(char *str, char *s)
{
	char *tmp_s = s;
	char *tmp_str = str;
	int size = 0;
	int count = 0;

	while (size == 0 && *tmp_s != '\0')
		size = find_globbings_size(tmp_s++);
	tmp_s = tmp_s - 1;
	if (*tmp_s == '\0')
		return (1);
	while (strncmp(tmp_str, tmp_s, size) && count < my_strlen(str)) {
		tmp_str = tmp_str + 1;
		count = count + 1;
	}
	if (my_strncmp(tmp_str, tmp_s, size))
		return (match(tmp_str, tmp_s + size));
	if (count + 1 > my_strlen(str))
		return (0);
	return (1);
}