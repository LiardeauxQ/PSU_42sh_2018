/*
** EPITECH PROJECT, 2017
** lib
** File description:
** remove_needless_char.c
*/

#include "my.h"

char *remove_useless_char(char *str, char *c)
{
	int i = 0;
	char tmp = 0;

	while (str[0] != '\0' && check_same_caractere(str[0], c)) {
		for (int j = 0 ; str[j] != '\0' ; j++)
			str[j] = str[j + 1];
		i = i + 1;
	}
	i = my_strlen(str) - 1;
	while (i > 0 && check_same_caractere(str[i], c)) {
		str[i] = '\0';
		i = i - 1;
	}
	return (str);
}
