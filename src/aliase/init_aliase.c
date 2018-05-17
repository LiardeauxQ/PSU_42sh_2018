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

void my_alias(cmd_t *cmd)
{}

void my_unalias(cmd_t *cmd)
{}
