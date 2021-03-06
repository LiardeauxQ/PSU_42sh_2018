/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** arrow_char_redirection.c
*/

#include "minishell.h"

int simple_left_arrow(shell_t *shell, cmd_t *cmd, char *filename,
	fildes_pipe_t *fd_pr)
{
	int fd = 0;
	int status = 0;

	if (shell->env == NULL || cmd == NULL || filename == NULL)
		return (-1);
	choose_dup_fd(fd_pr);
	if ((fd = open(filename, O_RDONLY)) == -1) {
		my_puterror(filename);
		my_puterror(": No such file or directory.\n");
		return (1);
	}
	if (dup2(fd, 0) == 1)
		return (-1);
	cmd->argv = remove_redir_char(cmd->argv);
	status = check_one_command(cmd, shell);
	close(fd);
	return (status);
}

int simple_right_arrow(shell_t *shell, cmd_t *cmd, char *filename,
	fildes_pipe_t *fd_pr)
{
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int fd = 0;
	int status = 0;

	if (shell->env == NULL || cmd == NULL || filename == NULL)
		return (-1);
	choose_dup_fd(fd_pr);
	if ((fd = open(filename, O_CREAT
		| O_WRONLY | O_TRUNC, mode)) == -1) {
		my_puterror(filename);
		my_puterror(": No such file or directory.\n");
		return (1);
	}
	if (dup2(fd, 1) == -1)
		return (-1);
	cmd->argv = remove_redir_char(cmd->argv);
	status = check_one_command(cmd, shell);
	close(fd);
	return (status);
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

int double_left_arrow(shell_t *shell, cmd_t *cmd, char *end_str,
	fildes_pipe_t *fd_pr)
{
	int fds[2] = {0, 0};
	int status = 0;

	if (shell->env == NULL || cmd == NULL || end_str == NULL)
		return (-1);
	choose_dup_fd(fd_pr);
	if (pipe(fds) == -1)
		return (-1);
	write_double_left_arrow(end_str, fds);
	if (dup2(fds[0], 0) == -1)
		return (-1);
	close(fds[1]);
	cmd->argv = remove_redir_char(cmd->argv);
	status = check_one_command(cmd, shell);
	close(fds[0]);
	return (status);
}

int double_right_arrow(shell_t *shell, cmd_t *cmd, char *filename,
	fildes_pipe_t *fd_pr)
{
	int fd = 0;
	int status = 0;

	if (shell->env == NULL || cmd == NULL || filename == NULL)
		return (-1);
	choose_dup_fd(fd_pr);
	if ((fd = open(filename, O_RDWR | O_APPEND)) == -1) {
		my_puterror(filename);
		my_puterror(": No such file or directory.\n");
		return (1);
	}
	if (dup2(fd, 1) == -1)
		return (-1);
	cmd->argv = remove_redir_char(cmd->argv);
	status = check_one_command(cmd, shell);
	close(fd);
	return (status);
}
