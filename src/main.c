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

	find_cmd_completion(av[1], my_strlen(av[1]), atoi(av[2]));
	/*while (quit != -1 && quit != 255) {
		my_putstr("$> ");
		buf = (isatty(fd)) ? read_line_cmd(fd) : get_next_line(fd);
		if (buf == NULL)
			break;
		quit = manage_multiple_commande(buf, &env);
		free(buf);
	}*/
	return ((quit == -1 || quit == 255) ? (0) : quit);
}