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

	while (quit != -1 && quit != 255) {
		my_putstr("$> ");
		buf = get_next_line(0);
		if (buf == NULL)
			break;
		quit = manage_multiple_commande(buf, &env);
		free(cmd);
		free(buf);
	}
	return ((quit == -1 || quit == 255) ? (0) : quit);
}
