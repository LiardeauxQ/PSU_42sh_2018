/*
** EPITECH PROJECT, 2017
** linked_list
** File description:
** print_list.c
*/

#include "linked_list.h"

int print_list(list_t *list)
{
	list_t *tmp = list;

	while (tmp != NULL) {
		puts(tmp->data);
		tmp = tmp->next;
	}
	return (0);
}
