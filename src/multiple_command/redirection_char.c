/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** redirection_char.c
*/

#include "minishell.h"

int check_if_redirection(char **split_cmd)
{
	for (int i = 0 ; split_cmd[i] != NULL ; i++) {
		if (my_strcmp("<", split_cmd[i]) == 1)
			return (1);
		if (my_strcmp(">", split_cmd[i]) == 1)
			return (2);
		if (my_strcmp("<<", split_cmd[i]) == 1)
			return (3);
		if (my_strcmp(">>", split_cmd[i]) == 1)
			return (4);
	}
	return (0);
}

int check_redirections_char(cmd_t *cmd, int pos)
{
	int type = 0;

	type = check_if_redirection(cmd[pos].argv);
	if (type == 2 || type == 4)
		return ((cmd[pos + 1].separator != -1)
		? OUTPUT_REDIR_ERROR : type);
	else if (type == 1 || type == 3)
		return ((pos != 0) ? INPUT_REDIR_ERROR : type);
	return (0);
}

char **remove_redir_char(char **argv)
{
	for (int i = 0 ; argv[i] != NULL ; i++) {
		if (my_strcmp(argv[i], ">"))
			argv[i] = NULL;
		if (my_strcmp(argv[i], "<"))
			argv[i] = NULL;
		if (my_strcmp(argv[i], ">>"))
			argv[i] = NULL;
		if (my_strcmp(argv[i], "<<"))
			argv[i] = NULL;
	}
	return (argv);
}

redir redir_init(void)
{
	int (*(*redirection))(char ***, cmd_t *, char *, fildes_pipe_t *);

	redirection = malloc(4 * sizeof(redirection));
	check_malloc(redirection);
	redirection[0] = simple_left_arrow;
	redirection[1] = simple_right_arrow;
	redirection[2] = double_left_arrow;
	redirection[3] = double_right_arrow;
	return (redirection);
}

int manage_redirection(cmd_t *cmd, char ***env, int type, fildes_pipe_t *fd_pr)
{
	int size = count_2d_array(cmd->argv);
	int (**redir)(char ***, cmd_t *, char *, fildes_pipe_t *) =
	redir_init();
	int quit = 0;
	int wstatus = 0;
	int pid = 0;

	if (cmd == NULL || env == NULL)
		return (0);
	if ((pid = fork()) == 0) {
		if (type != 0)
			quit = redir[type - 1](env, cmd, cmd->argv[size - 1],
				fd_pr);
		exit(quit);
	} else if (pid > 0) {
		close_files(fd_pr);
		waitpid(pid, &wstatus, 0);
		quit = wstatus;
	}
	return (quit);
}
