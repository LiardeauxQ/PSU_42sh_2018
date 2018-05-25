/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** main.c
*/

#include "minishell.h"

int main(int __attribute__((unused)) ac, char __attribute__((unused)) *av[],
char *env[])
{
	char *buf = NULL;
	int quit = 0;
	int fd = 0;
	int fd_hist = open(".42sh_history", O_CREAT | O_RDWR | O_APPEND, 00744);
	shell_t shell = {env, NULL, new_list_alias()};

	while (quit != -1 && quit != 255) {
		my_putstr("$> ");
		buf = (isatty(fd)) ? read_line_cmd(fd) : get_next_line(fd);
		if (buf == NULL)
			break;
		quit = manage_multiple_commande(buf, &shell);
		stock_history(fd_hist, buf);
		free(buf);
	}
	close(fd_hist);
	return ((quit == -1 || quit == 255) ? (0) : quit);
}
