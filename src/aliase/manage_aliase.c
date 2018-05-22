/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_aliase.c
*/

#include "minishell.h"

int my_unalias(list_alias_t *list_alias, char *cmd)
{
	is_unalias(list_alias, cmd);
	return (0);
}

int my_alias(list_alias_t *list_alias, char *cmd)
{
	int bef_equal = 0;
	int aft_equal = 0;
	char *old_cmd = NULL;
	char *new_cmd = NULL;

	if (cmd == NULL)
		return (1);
	if (count_equal(cmd) == 1)
		return (1);
	bef_equal = count_str_size(cmd, 0);
	aft_equal = count_str_size(cmd, bef_equal + 1);
	printf("%d, %d", bef_equal, aft_equal);
	old_cmd = malloc(sizeof(char *) * (bef_equal));
	new_cmd = malloc(sizeof(char *) * (aft_equal));
	old_cmd = new_str(cmd, 0, old_cmd);
	new_cmd = new_str(cmd, bef_equal + 1, new_cmd);
	printf("\n%s : %s\n", old_cmd, new_cmd);
	list_alias = push_back_list_alias(list_alias, old_cmd, new_cmd);
	print_list(list_alias);
	free(old_cmd);
	free(new_cmd);
	return (0);
}

char *is_alias(list_alias_t *list_alias, char *cmd)
{
	if (is_empty_list(list_alias)) {
		printf("empty list\n");
		return (NULL);
	}
	while (list_alias != NULL) {
		if (list_alias->cmd == cmd)
			return (list_alias->new_cmd);
		list_alias = list_alias->next;
	}
	return (NULL);
}

char *is_unalias(list_alias_t *list_alias, char *cmd)
{
	if (is_empty_list(list_alias)) {
		printf("empty list\n");
		return (NULL);
	}
	while (list_alias != NULL) {
		if (list_alias->cmd == cmd) {
			free(list_alias->cmd);
			free(list_alias->new_cmd);
		}
		list_alias = list_alias->next;
	}
	return (NULL);
}
