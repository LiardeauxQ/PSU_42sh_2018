/*
** EPITECH PROJECT, 2017
** my_strcpy.c
** File description:
** copy a string
*/

#include <stdio.h>
#include "my.h"

char *my_strcpy(char *dest, char const *src)
{
	int i = 0;

	if (dest == NULL || src == NULL)
		return (NULL);
	while (src[i] != '\0') {
		dest[i] = src[i];
		i = i + 1;
	}
	dest[i] = '\0';
	return (dest);
}

char **my_strcpy_2d_array(char **dest, char **src)
{
	int i = 0;
	int j = 0;

	if (dest == NULL || src == NULL)
		return (NULL);
	while (src[i] != NULL) {
		dest[i][j] = src[i][j];
		j = j + 1;
		if (j == my_strlen(src[i])) {
			dest[i][j] = '\0';
			i = i + 1;
			j = 0;
		}
	}
	dest[i] = NULL;
	return (dest);
}
