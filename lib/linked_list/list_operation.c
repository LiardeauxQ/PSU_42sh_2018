/*
** EPITECH PROJECT, 2017
** linked_list
** File description:
** push.c
*/

#include "linked_list.h"

int append(list_t *list, char *value)
{
	list_t *tmp = list;

	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(list_t));
	tmp->next->data = strdup(value);
	tmp->next->next = NULL;
	return (0);
}

int push(list_t **list, char *value)
{
	list_t *new = NULL;

	new = malloc(sizeof(list_t));
	new->data = strdup(value);
	new->next = *list;
	*list = new;
	return (0);
}

int print_list(list_t *list)
{
	list_t *tmp = list;

	while (tmp != NULL) {
		puts(tmp->data);
		tmp = tmp->next;
	}
	return (0);
}

int pop(list_t **list)
{
	list_t *save = NULL;

	if (*list == NULL)
		return (-1);
	save = (*list)->next;
	free((*list)->data);
	free(*list);
	*list = save;
	return (0);
}

void swap(list_t **elem1, list_t **elem2)
{
	char *tmp = NULL;

	tmp = strdup((*elem1)->data);
	free((*elem1)->data);
	(*elem1)->data = strdup((*elem2)->data);
	free((*elem2)->data);
	(*elem2)->data = strdup(tmp);
}

int remove_last(list_t **list)
{
	list_t *tmp = *list;

	if ((*list)->next == NULL) {
		free((*list)->data);
		free(*list);
		return (1);
	}
	while (tmp->next->next != NULL)
		tmp = tmp->next;
	free(tmp->next->data);
	free(tmp->next);
	tmp->next = NULL;	
	return (0);
}

void destroy_list(list_t *list)
{
	while (remove_last(&list) != 1);
}