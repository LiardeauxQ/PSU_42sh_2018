/*
** EPITECH PROJECT, 2017
** linked_list
** File description:
** count_list_size.c
*/

#include "linked_list.h"

int count_list_size(list_t *list)
{
	list_t *tmp = list;
	int size = 0;

	while (tmp != NULL) {
		size = size + 1;
		tmp = tmp->next;
	}
	return (size);
}