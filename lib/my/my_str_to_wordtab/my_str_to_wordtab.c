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

static int check_multiple_caractere(char *str, char *c, int i)
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

static char **initialize_str_to_tab_array(char *str, char *c)
{
	int size = count_char_rec(str, c);
	char **array = malloc(sizeof(char *) * (size + 1));

	check_malloc(array);
	for (int i = 0 ; i < size ; i++) {
		array[i] = malloc(my_strlen(str) + 1);
		check_malloc(array[i]);
	}
	return (array);
}

char **my_str_to_wordtab(char *str, char *c)
{
	char **tab_str = NULL;
	int j = 0;
	int k = 0;

	if (str == NULL || c == NULL || my_strlen(str) == 0)
		return (NULL);
	tab_str = initialize_str_to_tab_array(str, c);
	j = check_multiple_caractere(str, c, 0);
	for (int a = 0 ; j < my_strlen(str) ; a = a) {
		tab_str[k][a] = str[j];
		j = j + 1;
		a = a + 1;
		if (str[j] == '\0' || (check_same_caractere(str[j], c) == 1)) {
			j = check_multiple_caractere(str, c, j);
			tab_str[k][a] = '\0';
			a = 0;
			k = k + 1;
		}
	}
	tab_str[k] = NULL;
	return (tab_str);
}
