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

	while (quit != -1 && quit != 255) {
		my_putstr("$> ");
		buf = read_line_cmd();
		if (buf == NULL)
			break;
		quit = manage_multiple_commande(buf, &env);
		free(buf);
	}
	return ((quit == -1 || quit == 255) ? (0) : quit);
}
/*	while (quit != -1 && quit != 255) {
		my_putstr("$> ");
		buf = get_next_line(0);
		fprintf(stdout, "%s\n", buf);
		if (buf == NULL)
			break;
		quit = manage_multiple_commande(buf, &env);
		free(buf);
	}*/ 