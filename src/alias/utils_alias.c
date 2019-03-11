/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** utils_alias.c
*/

#include "minishell.h"

char *new_str(char *cmd, int size, char *new_cmd)
{
	int i = 0;
	while (cmd[size] != '\0' && cmd[size] != '=') {
		if (cmd[size] == '=')
			size += 1;
		new_cmd[i] = cmd[size];
		i++;
		size++;
	}
	new_cmd[i] = '\0';
	return (new_cmd);
}

int count_equal(char *str)
{
	int equal = 0;
	int i = 0;

	while (str[i] != '\0') {
		if (str[i] == '=')
			equal += 1;
		i++;
	}
	if (equal != 1)
		return (1);
	return (0);
}

int count_str_size(char *str, int i)
{
	int j = 0;

	while (str[i] != '=' && str[i] != '\0') {
		i++;
		j++;
	}
	return (j);
}

int remove_last_alias(list_alias_t **list_alias)
{
	list_alias_t *tmp = *list_alias;

	if (*list_alias != NULL && (*list_alias)->next == NULL) {
		free((*list_alias)->cmd);
		free((*list_alias)->new_cmd);
		free((*list_alias));
		return (1);
	}
	while (tmp->next->next != NULL)
		tmp = tmp->next;
	free(tmp->next->cmd);
	free(tmp->next->new_cmd);
	tmp->next = NULL;
	return (0);
}

void destroy_list_alias(list_alias_t *list_alias)
{
	while (remove_last_alias(&list_alias) != 1);
}
