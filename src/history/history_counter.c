/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** history counter
*/

#include "minishell.h"

void display_history_count(int number)
{
	int fd = open("src/history/.42sh_history", O_RDWR | O_APPEND);
	char *buf = NULL;
	int i = 0;
	int j = 0;

	while ((buf = get_next_line(fd)) != NULL) {
		i = i + 1;
		free(buf);
	}
	close(fd);
	fd = open("src/history/.42sh_history", O_RDWR | O_APPEND);
	while ((buf = get_next_line(fd)) != NULL) {
		if (j >= i - number) {
			my_putstr(buf);
			my_putchar('\n');
		}
		free(buf);
		j = j + 1;
	}
	close(fd);
}
