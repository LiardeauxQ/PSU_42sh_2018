/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** arrow_char_redirection.c
*/

#include "minishell.h"

int simple_left_arrow(char ***env, char *cmd, char *filename,
	fildes_pipe_t *fd_pr)
{
	char **argv = my_str_to_wordtab(cmd, " \t");
	int fd = 0;

	if (env == NULL || cmd == NULL || filename == NULL)
		return (-1);
	choose_dup_fd(fd_pr);
	if ((fd = open(filename, O_RDONLY)) == -1) {
		my_puterror(filename);
		my_puterror(": No such file or directory.\n");
		return (1);
	}
	if (dup2(fd, 0) == 1)
		return (-1);
	check_one_command(cmd, argv, env);
	close(fd);
	destroy_2darray(argv);
	return (0);
}

int simple_right_arrow(char ***env, char *cmd, char *filename,
	fildes_pipe_t *fd_pr)
{
	char **argv = my_str_to_wordtab(cmd, " \t");
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int fd = 0;

	if (env == NULL || cmd == NULL || filename == NULL)
		return (-1);
	choose_dup_fd(fd_pr);
	if ((fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)) == -1) {
		my_puterror(filename);
		my_puterror(": No such file or directory.\n");
		return (1);
	}
	if (dup2(fd, 1) == -1)
		return (-1);
	check_one_command(cmd, argv, env);
	close(fd);
	destroy_2darray(argv);
	return (0);
}

static void write_double_left_arrow(char *end_str, int *fds)
{
	char *buf = NULL;
	int quit = 0;

	if (end_str == NULL || fds == NULL)
		return;
	while (quit == 0) {
		my_putstr("? ");
		buf = get_next_line(0);
		if (my_strcmp(end_str, buf))
			quit = 1;
		else {
			write(fds[1], buf, my_strlen(buf));
			write(fds[1], "\n", 1);
		}
		free(buf);
	}
}

int double_left_arrow(char ***env, char *cmd, char *end_str,
	fildes_pipe_t *fd_pr)
{
	char **argv = my_str_to_wordtab(cmd, " \t");
	int fds[2] = {0, 0};

	if (env == NULL || cmd == NULL || end_str == NULL)
		return (-1);
	choose_dup_fd(fd_pr);
	if (pipe(fds) == -1)
		return (-1);
	write_double_left_arrow(end_str, fds);
	if (dup2(fds[0], 0) == -1)
		return (-1);
	close(fds[1]);
	check_one_command(cmd, argv, env);
	close(fds[0]);
	destroy_2darray(argv);
	return (0);
}

int double_right_arrow(char ***env, char *cmd, char *filename,
	fildes_pipe_t *fd_pr)
{
	char **argv = my_str_to_wordtab(cmd, " \t");
	int fd = 0;

	if (env == NULL || cmd == NULL || filename == NULL)
		return (-1);
	choose_dup_fd(fd_pr);
	if ((fd = open(filename, O_RDWR | O_APPEND)) == -1) {
		my_puterror(filename);
		my_puterror(": No such file or directory.\n");
		return (1);
	}
	if (dup2(fd, 1) == -1)
		return (-1);
	check_one_command(cmd, argv, env);
	close(fd);
	destroy_2darray(argv);
	return (0);
}
