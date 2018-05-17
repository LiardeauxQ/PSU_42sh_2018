/*
** EPITECH PROJECT, 2017
** lib
** File description:
** my_str_to_wordtab.c
*/

#include "../my.h"

int check_same_caractere(char str, char *c)
{
	for (int i = 0 ; c[i] != '\0' ; i++) {
		if (c[i] == str)
			return (1);
	}
	return (0);
}

int check_multiple_caractere(char *str, char *c, int i)
{
	while (str[i] != '\0' && (check_same_caractere(str[i], c) == 1))
		i = i + 1;
	return (i);
}

int count_char_rec(char *str, char *c)
{
	int size = 1;

	for (int i = 0 ; i < my_strlen(str) ; i++) {
		if (check_same_caractere(str[i], c) == 1)
			size = size + 1;
		i = check_multiple_caractere(str, c, i);
	}
	return (size);
}

char **my_str_to_wordtab(char *str, char *c)
{
	char *tmp = my_strdup(str);
	char *saveptr = NULL;
	char *token = strtok_r(tmp, c, &saveptr);
	char **array = NULL;
	int size = 1;

	while (token != NULL) {
		array = realloc(array, (size + 1) * sizeof(char *));
		array[size - 1] = my_strdup(token);
		tmp = NULL;
		token = strtok_r(tmp, c, &saveptr);
		size = size + 1;
	}
	array[size - 1] = NULL;
	free(tmp);
	return (array);
}
