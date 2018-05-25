/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** init_list_aliase.c
*/

#include "minishell.h"

list_alias_t *new_list_alias(void)
{
	return NULL;
}

int is_empty_list(list_alias_t *list_alias)
{
	if (list_alias == NULL)
		return (1);
	return (0);
}

int list_length(list_alias_t *list_alias)
{
	int size = 0;

	if (!is_empty_list(list_alias)) {
		while (list_alias != NULL) {
			++size;
			list_alias = list_alias->next;
		}
	}
	return (size);
}

void print_list(list_alias_t *list_alias)
{
	if (is_empty_list(list_alias)) {
		printf("empty list\n");
		return;
	}
	while (list_alias != NULL) {
		printf("\n%s : %s\n\n", list_alias->cmd, list_alias->new_cmd);
		list_alias = list_alias->next;
	}
}

list_alias_t *push_back_list_alias(list_alias_t *list_alias, char *cmd,
	char *new_cmd)
{
	list_alias_t *element = malloc(sizeof(*element));
	list_alias_t *tmp;

	if (element == NULL) {
		printf("ERROR_ALLOCATION\n");
		exit(84);
	}
	element->cmd = strdup(cmd);
	element->new_cmd = strdup(new_cmd);
	element->next = NULL;
	if (is_empty_list(list_alias))
		return (element);
	tmp = list_alias;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = element;
	return (list_alias);
}
