/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** tab_completion.c
*/

#include "minishell.h"

list_t *add_cmd_to_list(char const *dirname, char const *cmd, list_t *cmd_list)
{
	list_t *list = 0x0;

	list = open_dir_for_comparaison(dirname, cmd);
	if (list == 0x0)
		return (cmd_list);
	for (list_t *tmp = list ; tmp != 0x0 ; tmp = tmp->next) {
		if (check_cmd_already_in(cmd_list, tmp->data) == 0)
			push(&cmd_list, tmp->data);
	}
	destroy_list(list);
	return (cmd_list);
}

char *cut_cmd(char *cmd, int cursor)
{
	char *str = strdup(cmd);

	return (str);
}

char *remove_cmd_dir_path(char *cmd)
{
	unsigned int delta = 0;
	int sep = -1;

	for (int i = my_strlen(cmd) ; i >= 0 && cmd[i] != '/' ; i--)
		delta = i - 1;
	for (int j = my_strlen(cmd) ; j >= 0 && cmd[j] != ' '
	&& cmd[j] != '\t' && cmd[j] != '/' ; j--)
		sep = j;
	if (sep > 0)
		delta = sep - 1;
	if (delta < strlen(cmd) + 1)
		cmd = cmd + delta + 1;
	return (cmd);
}
