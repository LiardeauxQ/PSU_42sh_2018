/*
** EPITECH PROJECT, 2017
** linked_list
** File description:
** destroy_list.c
*/

#include "linked_list.h"

void destroy_list(list_t *list)
{
	while (remove_last(&list) != 1);
}
