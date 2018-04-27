/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_fd_redirection.c
*/

#include "minishell.h"

void change_fds_priority(fildes_pipe_t *fd_pr, int cmd_pos)
{
	if (fd_pr == NULL)
		return;
	for (int i = 0 ; fd_pr->fildes[i] != -1 ; i++)
		fd_pr->action_rw[i] = 0;
	cmd_pos += cmd_pos;
	if (cmd_pos != 0)
		fd_pr->action_rw[cmd_pos - 2] = 1;
	if (fd_pr->fildes[cmd_pos] != -1)
		fd_pr->action_rw[cmd_pos + 1] = 2;
}

void choose_dup_fd(fildes_pipe_t *fd_pr)
{
	if (fd_pr == NULL)
		return;
	for (int i = 0 ; fd_pr->fildes[i] != -1 ; i++) {
		if (fd_pr->action_rw[i] == 1)
			dup2(fd_pr->fildes[i], 0);
		else if (fd_pr->action_rw[i] == 2)
			dup2(fd_pr->fildes[i], 1);
		else
			close(fd_pr->fildes[i]);
	}
}

void close_files(fildes_pipe_t *fd_pr)
{
	if (fd_pr == NULL)
		return;
	for (int k = 0 ; fd_pr->fildes[k] != -1 ; k++)
		if (fd_pr->action_rw[k] != 0)
			close(fd_pr->fildes[k]);
}

fildes_pipe_t initialize_tmp_fildes_descriptor(cmd_t *cmd)
{
	fildes_pipe_t fd_pr = {NULL, NULL, 0};
	int j = 0;

	if (cmd == NULL)
		return (fd_pr);
	for (int i = 0 ; cmd[i].separator != -1 ; i++)
		fd_pr.size += 1;
	fd_pr.fildes = malloc((fd_pr.size * 2 + 1) * sizeof(int));
	check_malloc(fd_pr.fildes);
	fd_pr.action_rw = malloc((fd_pr.size * 2 + 1) * sizeof(int));
	check_malloc(fd_pr.action_rw);
	while (j < (fd_pr.size - 1) * 2) {
		if (pipe(fd_pr.fildes + j) == -1) {
			fd_pr.size = -1;
			my_puterror("Alias loop.\n");
		}
		j = j + 2;
	}
	fd_pr.fildes[j] = -1;
	return (fd_pr);
}

void destroy_fildes_pipe(fildes_pipe_t *fd_pr)
{
	free(fd_pr->fildes);
	free(fd_pr->action_rw);
}
