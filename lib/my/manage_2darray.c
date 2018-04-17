/*
** EPITECH PROJECT, 2017
** manage_2darray.c
** File description:
** functions in order to manage 2d array
*/

#include "my.h"

void destroy_2darray(char **array)
{
	if (array == NULL)
		return;
	for (int i = 0 ; array[i] != NULL ; i++)
		free(array[i]);
	free(array);
}

int count_2d_array(char **array)
{
	int size = 0;

	if (array == NULL)
		return (0);
	for (int i = 0 ; array[i] != NULL ; i++)
		size = size + 1;
	return (size);
}

int count_words(char str[])
{
	int size = 0;

	for (int i = 0 ; str[i] != '\0' ; i++) {
		if (str[i] == ' ' || str[i] == '\t')
			size = size + 1;
	}
	size = size + 1;
	return (size);
}
