/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_aliase.c
*/

#include "minishell.h"

int is_str(char c, char *seps)
{
	int n = 0;

	while (seps[n]) {
		if (c == seps[n])
			return (0);
		n++;
	}
	return (1);
}

int words_count(char *str, char *seps)
{
	int n = 0;
	int words = 0;

	while (str[n]) {
		if (is_str(str[n], seps))
			words++;
		while (is_str(str[n], seps) && str[n])
			n++;
	if (str[n] != '\0')
		n++;
	}
	return (words);
}

int words_lenght(char *str, int word, char *seps)
{
	int n = 0;
	int words = 0;
	int lenght = 0;

	while (str[n]) {
		if (is_str(str[n], seps))
			words++;
		while (is_str(str[n], seps) && str[n]) {
			if (words == word)
				lenght++;
			n++;
		}
	if (str[n] != '\0')
		n++;
	}
	return (lenght);
}

char *words_get(char *str, int word, char *seps)
{
	int n = 0;
	int words = 0;
	char *tmp;
	int i = 0;

	if ((tmp = malloc(words_lenght(str, word, seps) + 1)) == NULL)
		return (NULL);
	while (str[n]) {
		if (is_str(str[n], seps))
			words++;
		while (is_str(str[n], seps) && str[n]) {
			if (words == word)
				tmp[i++] = str[n];
			n++;
		}
	if (str[n] != '\0')
		n++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char *tab_to_str(char **tab)
{
	int i = 0;
	char *str;
	int len = 0;

	while (tab[i] != NULL)
		len = len + strlen(tab[i++]) + 1;
	if ((str = malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	i = 0;
	if (str != NULL)
		str[0] = '\0';
	while (tab[i] != NULL) {
		strcat(str, tab[i]);
		if (tab[i + 1] != NULL)
			strcat(str, " ");
		i++;
	}
	return (str);
}
