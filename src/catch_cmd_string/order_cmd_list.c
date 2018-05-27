/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** order_cmd_list.c
*/

#include "minishell.h"

int compare_str_alpha(list_t *list)
{
	for (int i = 0 ; list->data[i] != '\0'
	&& list->next->data[i] != '\0' ; i++) {
		if (list->data[i] > list->next->data[i])
			return (1);
	}
	return (0);
}

list_t *order_list(list_t *cmd_list)
{
	int order = 0;

	if (cmd_list == NULL)
		return (NULL);
	for (list_t *tmp = cmd_list ; tmp->next != NULL ; tmp = tmp->next) {
		if (compare_str_alpha(tmp))
			swap(&tmp, &tmp->next);
	}
	for (list_t *tmp = cmd_list ; tmp->next != NULL ; tmp = tmp->next)
		if (compare_str_alpha(tmp))
			order = 1;
	if (order == 1)
		return (order_list(cmd_list));
	return (cmd_list);
}