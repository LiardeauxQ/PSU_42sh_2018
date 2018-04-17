/*
** EPITECH PROJECT, 2017
** get_next_line.c
** File description:
** get next line
*/

#include "my.h"

static void set_new_buffer(char buffer[], int i)
{
	int k = 0;
	int size = 0;

	size = my_strlen(buffer);
	for (int j = i ; j < size ; j++) {
		buffer[k] = buffer[j];
		k = k + 1;
	}
	while (k < size) {
		buffer[k] = '\0';
		k = k + 1;
	}
}

static char *my_realloc(char *array, int size)
{
	char *new_array = NULL;
	int i = 0;

	new_array = malloc((my_strlen(array) + size) * 2);
	check_malloc(new_array);
	if (new_array == NULL)
		return (NULL);
	while (array[i] != '\0') {
		new_array[i] = array[i];
		i = i + 1;
	}
	new_array[i] = '\0';
	free(array);
	return (new_array);
}

static int file_line(char buffer[], char *stock_line, int *j)
{
	int i = 0;

	while (buffer[i] != '\0' && buffer[i] != '\n') {
		stock_line[*j] = buffer[i];
		i = i + 1;
		*j = *j + 1;
	}
	stock_line[*j] = '\0';
	if (buffer[i] == '\n') {
		i = i + 1;
		set_new_buffer(buffer, i);
		return (1);
	}
	return (0);
}

static char *read_file(char *stock_line, char buffer[], int fd, int *rd)
{
	int j = 0;

	if (my_strlen(buffer) != 0) {
		if (file_line(buffer, stock_line, &j))
			return (stock_line);
	}
	while ((*rd = read(fd, buffer, READ_SIZE)) != 0) {
		buffer[*rd] = '\0';
		if (*rd == -1)
			return (NULL);
		if (file_line(buffer, stock_line, &j))
			break;
		if ((stock_line = my_realloc(stock_line, READ_SIZE)) == NULL)
			return (NULL);
		for (int i = 0 ; buffer[i] != '\0' ; i++)
			buffer[i] = '\0';
	}
	if (*rd == 0)
		for (int i = 0 ; buffer[i] != '\0' ; i++)
			buffer[i] = '\0';
	return (stock_line);
}

char *get_next_line(int fd)
{
	static char buffer[READ_SIZE + 1];
	char *stock_line = NULL;
	int rd = 0;

	if (fd == -1)
		return (NULL);
	if ((stock_line = malloc(READ_SIZE * 2)) == NULL)
		return (NULL);
	check_malloc(stock_line);
	stock_line[0] = '\0';
	if ((stock_line = read_file(stock_line, buffer, fd, &rd)) == NULL)
		return (NULL);
	if (my_strlen(stock_line) == 0 && my_strlen(buffer) == 0 && rd == 0) {
		free(stock_line);
		return (NULL);
	}
	return (stock_line);
}
