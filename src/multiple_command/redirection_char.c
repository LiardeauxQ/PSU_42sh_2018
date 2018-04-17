/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** redirection_char.c
*/

#include "minishell.h"

int check_if_redirection(char **splite_cmd)
{
	for (int i = 0 ; splite_cmd[i] != NULL ; i++) {
		if (my_strcmp("<", splite_cmd[i]) == 1)
			return (1);
		if (my_strcmp(">", splite_cmd[i]) == 1)
			return (2);
		if (my_strcmp("<<", splite_cmd[i]) == 1)
			return (3);
		if (my_strcmp(">>", splite_cmd[i]) == 1)
			return (4);
	}
	return (0);
}

int check_redirections_char(char ***splite_cmd, int pos)
{
	int type = 0;

	type = check_if_redirection(splite_cmd[pos]);
	if (type == 2 || type == 4)
		return ((splite_cmd[pos + 1] != NULL)
		? OUTPUT_REDIR_ERROR : type);
	else if (type == 1 || type == 3)
		return ((pos != 0) ? INPUT_REDIR_ERROR : type);
	return (0);
}

char *recup_cmd_without_redir(char *cmd)
{
	int i = my_strlen(cmd);

	while (i > 0 && cmd[i] != '>' && cmd[i] != '<') {
		cmd[i] = '\0';
		i = i - 1;
	}
	while (i > 0 && (cmd[i] == '>' || cmd[i] == '<' ||
	cmd[i] == ' ' || cmd[i] == '\t')) {
		cmd[i] = '\0';
		i = i - 1;
	}
	return (cmd);
}

redir redir_init(void)
{
	int (*(*redirection))(char ***, char *, char *, fildes_pipe_t *);

	redirection = malloc(4 * sizeof(redirection));
	check_malloc(redirection);
	redirection[0] = simple_left_arrow;
	redirection[1] = simple_right_arrow;
	redirection[2] = double_left_arrow;
	redirection[3] = double_right_arrow;
	return (redirection);
}

int manage_redirection(char *cmd, char ***env, int type, fildes_pipe_t *fd_pr)
{
	char **argv = my_str_to_wordtab(cmd, " \t");
	int size = count_2d_array(argv);
	int (**redir)(char ***, char *, char *, fildes_pipe_t *) = redir_init();
	int quit = 0;
	int wstatus = 0;
	int pid = 0;

	if (cmd == NULL || argv == NULL || env == NULL)
		return (0);
	cmd = recup_cmd_without_redir(cmd);
	if ((pid = fork()) == 0) {
		if (type != 0)
			quit = redir[type - 1](env, cmd, argv[size - 1], fd_pr);
		destroy_2darray(argv);
		exit(quit);
	} else if (pid > 0) {
		close_files(fd_pr);
		waitpid(pid, &wstatus, 0);
	}
	destroy_2darray(argv);
	return (quit);
}
