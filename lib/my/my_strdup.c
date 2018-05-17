/*
** EPITECH PROJECT, 2017
** my_strdup.c
** File description:
** my strdup
*/

#include "my.h"

char *my_strdup(char const *src)
{
	char *strdup = NULL;
	int i = 0;

	if (src == NULL)
		return (NULL);
	strdup = malloc(my_strlen(src) + 10);
	check_malloc(strdup);
	while (src[i] != '\0') {
		strdup[i] = src[i];
		i = i + 1;
	}
	strdup[i] = '\0';
	return (strdup);
}
