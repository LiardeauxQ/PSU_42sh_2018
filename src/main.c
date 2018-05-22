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
	cmd_t *cmd = NULL;
	int fd_hist = open("src/history/.42sh_history", O_CREAT | O_RDWR
	| O_APPEND, 00744);

	while (quit != -1 && quit != 255) {
		my_putstr("$> ");
		buf = get_next_line(0);
		if (buf == NULL)
			break;
		quit = manage_multiple_commande(buf, &env);
		stock_history(fd_hist, buf);
		free(cmd);
		free(buf);
	}
	close(fd_hist);
	return ((quit == -1 || quit == 255) ? (0) : quit);
}
