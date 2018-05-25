/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_aliase.c
*/

#include "minishell.h"

list_alias_t *my_unalias(list_alias_t *list_alias, char *cmd)
{
	is_unalias(list_alias, cmd);
	return (list_alias);
}

list_alias_t *my_alias(list_alias_t *list_alias, char *cmd)
{
	int bef_equal = 0;
	int aft_equal = 0;
	char *old_cmd = NULL;
	char *new_cmd = NULL;

	if (cmd == NULL)
		return (NULL);
	if (count_equal(cmd) == 1)
		return (NULL);
	bef_equal = count_str_size(cmd, 0);
	aft_equal = count_str_size(cmd, bef_equal + 1);
	old_cmd = malloc(sizeof(char *) * (bef_equal));
	new_cmd = malloc(sizeof(char *) * (aft_equal));
	old_cmd = new_str(cmd, 0, old_cmd);
	new_cmd = new_str(cmd, bef_equal + 1, new_cmd);
	list_alias = push_back_list_alias(list_alias, old_cmd, new_cmd);
	free(old_cmd);
	free(new_cmd);
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

char *is_unalias(list_alias_t *list_alias, char *cmd)
{
	if (is_empty_list(list_alias)) {
		printf("unalias: no such hash table element: %s\n", cmd);
		return (NULL);
	}
	while (list_alias != NULL) {
		if (my_strcmp(list_alias->cmd, cmd)) {
			free(list_alias->cmd);
			free(list_alias->new_cmd);
		}
		list_alias = list_alias->next;
	}
	return (NULL);
}
