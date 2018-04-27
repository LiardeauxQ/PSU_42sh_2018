/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** print_cmd_struct.c
*/

#include "minishell.h"

void display_cmd(cmd_t *cmd)
{
	if (cmd == NULL)
		return;
	printf("cmd\n");
	for (int i = 0 ; cmd[i].separator != -1 ; i++) {
		printf("%d . cmd : %s separator %d\n", i, cmd[i].cmd,
		cmd[i].separator);
		if (cmd[i].argv != NULL) {
			for (int j = 0 ; cmd[i].argv[j] != NULL ; j++) {
				printf("argv : %s\n", cmd[i].argv[j]);
			}
		}
		display_cmd(cmd[i].childs);
	}
}
