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
	char *str_cut = malloc((cursor + 1) * sizeof(char));
	int i = 0;
	int j = 0;

	check_malloc(str_cut);
	if (strlen(cmd) >= 2 && cmd[0] == '.' && cmd[1] == '/')
		i = 2;
	while (i < cursor) {
		str_cut[j] = cmd[i++];
		j = j + 1;
	}
	str_cut[j] = '\0';
	return (str_cut);
}

char *remove_cmd_dir_path(char *cmd)
{
	unsigned int delta = 0;
	int sep = -1;

	for (int i = 0 ; cmd[i] != '\0' && cmd[i] != '/' ; i++)
		delta += 1;
	for (int j = my_strlen(cmd) - 1 ; j > 0 && cmd[j] != ' '
	&& cmd[j] != '\t' ; j--)
		sep = j;
	if (sep != -1) {
		delta = sep;
	}
	if (delta != strlen(cmd))
		cmd = cmd + delta + 1;
	//printf("cmd %s %d\n", cmd, delta);
	return (cmd);
}