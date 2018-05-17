/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** manage history
*/

#include "minishell.h"

int count_id(int fd)
{
	char *buf = NULL;
	int j = 0;
	int i = 0;
	struct stat stats;

	stat("src/history/.42sh_history", &stats);
	buf = malloc((stats.st_size + 1) * sizeof(char));
	lseek(fd, 0, SEEK_SET);
	i = read(fd, buf, stats.st_size);
	if (i != 0) {
		buf[i] = '\0';
		i = 0;
		while (buf[i] != '\0') {
			if (buf[i] == '\n')
				j = j + 1;
			i = i + 1;
		}
	}
	free(buf);
	return (j);
}

void stock_history(int fd, char *buf)
{
	char buf_time[21];
	int j = count_id(fd);
	char *num = int_tostr(j);

	time_t t = time(NULL);
	strftime(buf_time, sizeof(buf_time), "%b %d - %X :\t", localtime(&t));
	write(fd, num, my_strlen(num));
	write(fd, ":\t", 2);
	write(fd, buf_time, my_strlen(buf_time));
	write(fd, buf, my_strlen(buf));
	write(fd, "\n", 1);
	free(num);
}
