/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** init_aliase.c
*/

#include "minishell.h"

list_t *list_create()
{
	list_t *new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->next = new;
	new->prev = new;
	new->key = strdup("\0");
	return (new);
}

list_t *list_add(list_t *list, char *key, char *content)
{
	list_t *new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->key = key;
	new->content = content;
	new->next = list;
	new->prev = list->prev;
	list->prev->next = new;
	list->prev = new;
	return (new);
}

void list_delete_node(list_t *node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
	if (node->key != NULL)
		free(node->key);
	if (node->content != NULL && my_strcmp(node->content, "") != 0)
		free(node->content);
	free(node);
}

list_t *get_node_by_key(list_t *list, char *key)
{
	list_t *tmp = list->next;

	while (tmp != list) {
		if (xstrcmp(key, tmp->key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int list_count(list_t *list)
{
	list_t *tmp = list->next;
	int count = 0;

	while (tmp != list) {
		count++;
		tmp = tmp->next;
	}
	return (count);
}
