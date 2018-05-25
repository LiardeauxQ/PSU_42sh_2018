/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** manage history
*/

#include "minishell.h"

void clear_history(void)
{
	int fd = open(".42sh_history", O_RDWR | O_TRUNC);

	close(fd);
}

void display_history(void)
{
	int fd = open(".42sh_history", O_RDWR | O_APPEND);
	char *buf = NULL;

	while ((buf = get_next_line(fd)) != NULL) {
		my_putstr(buf);
		my_putchar('\n');
		free(buf);
	}
	close(fd);
}

int manage_history_command(char ***env, char **argv)
{
	int nb_arg = count_2d_array(argv);
	int i = 0;

	if (nb_arg == 1) {
		display_history();
		return (0);
	} else if (nb_arg == 2 && my_strcmp(argv[1], "-c")) {
		clear_history();
		return (0);
	}
	if (nb_arg == 2 && (i = my_strtoi_error(argv[1])) != -1)
		display_history_count(i);
	return (0);
}

int count_id(int fd)
{
	char *buf = NULL;
	int j = 0;
	int i = 0;
	struct stat stats;

	stat(".42sh_history", &stats);
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
	strftime(buf_time, sizeof(buf_time), "%b %d - %X:\t", localtime(&t));
	write(fd, num, my_strlen(num));
	write(fd, ":\t", 2);
	write(fd, buf_time, my_strlen(buf_time));
	write(fd, buf, my_strlen(buf));
	write(fd, "\n", 1);
	free(num);
}
