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

char *add_dir_to_path(char *cmd)
{
	char *new_pwd = NULL;
	int size = my_strlen(cmd);
	int path_pos = 0;
	int space_pos = 0;
	int j = 0;

	if (!cinstr(cmd, '/'))
		return (my_strdup("./"));
	for (int i = size ; i >= 0 && cmd[i] != '/' ; i--)
		path_pos = i;
	for (int k = size ; k >= 0 && cmd[k] != ' ' && cmd[k] != '\t' ; k--)
		space_pos = k;
	if (space_pos > path_pos)
		return (my_strdup("./"));
	new_pwd = malloc((size + 1) * sizeof(char));
	for (int a = space_pos ; cmd[a] != '\0' && a < path_pos ; a++) {
		new_pwd[j] = cmd[a];
		j = j + 1;
	}
	new_pwd[j] = '\0';
	return (new_pwd);
}