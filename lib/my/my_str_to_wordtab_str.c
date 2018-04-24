/*
** EPITECH PROJECT, 2017
** lib
** File description:
** my_strtotab.c
*/

#include "my.h"

int check_if_str_in_str(char *str1, char *str2)
{
	int size1 = my_strlen(str1);
	int size2 = my_strlen(str2);
	int i = 0;
	int j = 0;

	if (str1 == NULL || str2 == NULL)
		return (0);
	while (i < size1) {
		j = 0;
		while (str2[j] != '\0' && str1[i] != '\0'
		&& (str2[j] == str1[i])) {
			i = i + 1;
			j = j + 1;
		}
		if (j == size2)
			return (i);
		i = i + 1;
	}
	return (-1);
}

int count_str_rec(char *str1, char *str2)
{
	int size = 1;
	int statu = 0;

	for (int i = 0 ; i < my_strlen(str1) ; i++) {
		statu = check_if_str_in_str(str1 + i, str2);
		if (statu == -1)
			break;
		else {
			i += statu;
			size = size + 1;
		}
	}
	return (size);
}

static int check_same_str(char *str1, char *str2)
{
	int i = 0;
	int j = 0;

	while (str1[i] != '\0' && str2[i] != '\0') {
		if (str1[i] != str2[i])
			return (0);
		i = i + 1;
	}
	return (1);
}

static char **initialize_double_array(char *str1, char *str2)
{
	int size = count_str_rec(str1, str2);
	char **array = malloc(sizeof(char *) * (size + 1));

	check_malloc(array);
	for (int i = 0 ; i < size ; i++) {
		array[i] = malloc(my_strlen(str1) + 1);
		check_malloc(array[i]);
	}
	return (array);
}

char **my_str_to_wordtab_str(char *str1, char *str2)
{
	char **tab_str = NULL;
	int j = 0;
	int k = 0;

	if (str1 == NULL || str2 == NULL || my_strlen(str1) == 0)
		return (NULL);
	tab_str = initialize_double_array(str1, str2);
	while (str1[j] != '\0' && check_same_str(str1 + j, str2) == 1)
		j = j + 1;
	for (int a = 0 ; j < my_strlen(str1) ; a = a) {
		tab_str[k][a] = str1[j];
		j = j + 1;
		a = a + 1;
		if (str1[j] == '\0' || (check_same_str(str1 + j, str2) == 1)) {
			tab_str[k][a] = '\0';
			a = 0;
			k = k + 1;
			j += my_strlen(str2);
		}
	}
	tab_str[k] = NULL;
	return (tab_str);
}
