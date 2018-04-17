/*
** EPITECH PROJECT, 2017
** libmy
** File description:
** manage_3d_array.c
*/

#include "my.h"

void check_malloc(void *array)
{
	if (array == NULL) {
		my_puterror("ERROR WITH MALLOC\n");
		exit(ERRROR_MALLOC);
	}
}

char ***create_3d_array(int size1, int size2)
{
	char ***array = NULL;
	int i = 0;

	if (size1 == 0 || size2 == 0)
		return (NULL);
	array = malloc((size1 + 1) * sizeof(char **));
	check_malloc(array);
	while (i < size1) {
		array[i] = malloc((size2 + 1) * sizeof(char *));
		check_malloc(array[i]);
		i = i + 1;
	}
	array[i] = NULL;
	return (array);
}

int count_3d_array(char ***array)
{
	int size = 0;

	if (array == NULL)
		return (0);
	for (int i = 0 ; array[i] != NULL ; i++)
		size = size + 1;
	return (size);
}

void destroy_3darray(char ***array)
{
	if (array == NULL)
		return;
	for (int i = 0 ; array[i] != NULL ; i++) {
		for (int j = 0 ; array[i][j] != NULL ; j++)
			free(array[i][j]);
		free(array[i]);
	}
	free(array);
}
