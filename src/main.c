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
	mysh_t *sh = malloc(sizeof(mysh_t));

	sh->alias = list_create();
	alias_initialize(sh->alias);
	while (quit != -1 && quit != 255) {
		my_putstr("$> ");
		buf = get_next_line(0);
		buf = alias_replace(sh->alias, buf);
		if (buf == NULL)
			break;
		if (my_strcmp(av[0], "alias"))
			return (my_alias(sh, av));
		else if (my_strcmp(av[0], "unalias"))
			return (my_unalias(sh, av));
		quit = manage_multiple_commande(buf, &env);
		free(buf);
	}
	return ((quit == -1 || quit == 255) ? (0) : quit);
}
