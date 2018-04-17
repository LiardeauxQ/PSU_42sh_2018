/*
** EPITECH PROJECT, 2017
** my_strcat.c
** File description:
** strcat.c
*/

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
	int i = my_strlen(dest);

	if (dest == NULL || src == NULL)
		return (NULL);
	for (int j = 0 ; src[j] != '\0' ; j++) {
		dest[i] = src[j];
		i = i + 1;
	}
	dest[i] = '\0';
	return (dest);
}
