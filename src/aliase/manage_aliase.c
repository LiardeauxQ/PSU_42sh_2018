/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_aliase.c
*/

#include "minishell.h"

list_alias_t *my_unalias(list_alias_t *list_alias, char **cmd)
{
	if (count_2d_array(cmd) == 2)
		list_alias = is_unalias(list_alias, cmd[1]);
	return (list_alias);
}

list_alias_t *my_alias(list_alias_t *list_alias, char **cmd)
{
	int size = count_2d_array(cmd);

	if (cmd == NULL)
		return (NULL);
	if (size >= 3)
		list_alias = push_back_list_alias(list_alias, cmd[2], cmd[1]);
	else if (size == 1)
		print_alias(list_alias);
	return (list_alias);
}

char *replace_alias(list_alias_t *list_alias, char *cmd)
{
	if (is_empty_list(list_alias))
		return (cmd);
	while (list_alias != NULL) {
		if (my_strcmp(list_alias->new_cmd, cmd)) {
			free(cmd);
			cmd = strdup(list_alias->cmd);
			return (cmd);
		}
		list_alias = list_alias->next;
	}
	return (cmd);
}

list_alias_t *is_unalias(list_alias_t *list_alias, char *cmd)
{
	list_alias_t *tmp;
	list_alias_t *previous;

	if (is_empty_list(list_alias)) {
		printf("unalias: no such hash table element: %s\n", cmd);
		return (NULL);
	}
	previous = list_alias;
	if (my_strcmp(list_alias->new_cmd, cmd)) {
		list_alias = previous->next;
		free(previous);
		return (list_alias);
	}
	tmp = previous->next;
	while (tmp != NULL) {
		if (my_strcmp(list_alias->new_cmd, cmd)) {
			previous->next = tmp->next;
			free(tmp);
			return (list_alias);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (list_alias);
}
