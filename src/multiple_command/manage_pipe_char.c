/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_pipe_char.c
*/

#include "minishell.h"

static char ***remove_pipe(char **splite_cmd, int size)
{
	int cmd_nbr = count_2d_array(splite_cmd);
	char ***argv = create_3d_array(size + 1, cmd_nbr + 1);
	int b = 0;
	int c = 0;

	if (argv == NULL || splite_cmd == NULL)
		return (NULL);
	for (int a = 0 ; a < cmd_nbr ; a = a) {
		argv[b][c] = my_strdup(splite_cmd[a]);
		a = a + 1;
		c = c + 1;
		if (my_strcmp("|", splite_cmd[a])) {
			argv[b][c] = NULL;
			a = a + 1;
			b = b + 1;
			c = 0;
		}
	}
	argv[b][c] = NULL;
	argv[b + 1] = NULL;
	return (argv);
}

static int manage_pipe_redirection(char *new_cmd, char **argv, char ***env,
	fildes_pipe_t *fd_pr)
{
	int value = 0;
	int status = 0;

	if (new_cmd == NULL || argv == NULL || env == NULL)
		return (0);
	value = fork();
	if (value == -1) {
		my_puterror("Error with fork()\n");
	} else if (value == 0) {
		choose_dup_fd(fd_pr);
		status = check_one_command(new_cmd, argv, env);
		exit(status);
	} else
		close_files(fd_pr);
	return (0);
}

int wait_all_process(char ***argv, int quit)
{
	int cmd_nbr = count_3d_array(argv);
	int wstatus = 0;
	int save_quit = quit;

	if (argv == NULL)
		return (0);
	for (int a = 0 ; a < cmd_nbr ; a++) {
		wait(&wstatus);
		if (quit == 0)
			quit = WEXITSTATUS(wstatus);
		else if (quit == 0)
			quit = check_exe_signal(wstatus);
	}
	return ((save_quit != 0) ? (save_quit) : (quit));
}

int manage_pipe(char *cmd, char **splite_cmd, char ***env)
{
	char **nw_cmd = remove_needless_char(my_str_to_wordtab(cmd, "|"));
	fildes_pipe_t fd_pr = initialize_tmp_fildes_descriptor(nw_cmd);
	char ***argv = remove_pipe(splite_cmd, fd_pr.size);
	int quit = check_if_redir_error(argv);

	if (argv == NULL || nw_cmd == NULL || env == NULL || quit < 0)
		return (quit);
	for (int i = 0 ; argv[i] != NULL && quit >= 0 ; i++) {
		change_fds_priority(&fd_pr, i);
		if ((quit = check_redirections_char(argv, i)) > 0)
			quit = manage_redirection(nw_cmd[i], env, quit, &fd_pr);
		else if (quit >= 0)
			quit = manage_pipe_redirection(nw_cmd[i], argv[i],
				env, &fd_pr);
	}
	quit = wait_all_process(argv, quit);
	for (int k = 0 ; fd_pr.fildes[k] != -1 ; k++)
		close(fd_pr.fildes[k]);
	destroy_3darray(argv);
	destroy_2darray(nw_cmd);
	return (quit);
}
