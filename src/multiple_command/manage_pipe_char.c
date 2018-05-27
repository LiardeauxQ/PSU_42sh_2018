/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_pipe_char.c
*/

#include "minishell.h"

static int manage_pipe_redirection(cmd_t *cmd, shell_t *shell,
fildes_pipe_t *fd_pr)
{
	int value = 0;
	int status = 0;

	if (shell->env == NULL)
		return (0);
	value = fork();
	if (value == -1) {
		my_puterror("Error with fork()\n");
	} else if (value == 0) {
		choose_dup_fd(fd_pr);
		status = check_one_command(cmd, shell);
		exit(status);
	} else
		close_files(fd_pr);
	return (0);
}

static int wait_all_process(cmd_t *cmd, int quit)
{
	int wstatus = 0;
	int save_quit = quit;

	if (cmd == NULL)
		return (0);
	for (int a = 0 ; cmd[a].separator != -1 ; a++) {
		wait(&wstatus);
		if (quit == 0)
			quit = WEXITSTATUS(wstatus);
		else if (quit == 0)
			quit = check_exe_signal(wstatus);
	}
	return ((save_quit != 0) ? (save_quit) : (quit));
}

int manage_pipe(cmd_t *cmd, shell_t *shell)
{
	fildes_pipe_t fd_pr = {NULL, NULL, 0};
	int quit = check_if_redir_error(cmd->childs);

	fd_pr = initialize_tmp_fildes_descriptor(cmd->childs);
	if (shell->env == NULL || quit < 0 || fd_pr.size == -1)
		return ((quit == 0) ? (1) : quit);
	for (int i = 0 ; cmd->childs[i].separator != -1 && quit >= 0 ; i++) {
		change_fds_priority(&fd_pr, i);
		if ((quit = check_redirections_char(cmd->childs, i)) > 0)
			quit = manage_redirection(&cmd->childs[i], shell, quit,
				&fd_pr);
		else if (quit >= 0)
			quit = manage_pipe_redirection(&cmd->childs[i], shell,
				&fd_pr);
	}
	quit = wait_all_process(cmd->childs, quit);
	for (int k = 0 ; fd_pr.fildes[k] != -1 ; k++)
		close(fd_pr.fildes[k]);
	destroy_fildes_pipe(&fd_pr);
	return (quit);
}
