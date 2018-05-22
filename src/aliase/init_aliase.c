/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** init_aliase.c
*/

#include "minishell.h"

void restore_alias(alias_t *new_element)
{
	int i = -1;

	while (new_element->cmd[++i] != '\0') {
		if (new_element->cmd[0] == '"')
			new_element->cmd[0] = ' ';
		if (new_element->cmd[i] == -1)
			new_element->cmd[i] = ' ';
	}
	if (strlen(new_element->cmd) > 0) {
		if (new_element->cmd[strlen(new_element->cmd) - 1] == '"')
			new_element->cmd[strlen(new_element->cmd) - 1] = ' ';
	}
}

int my_alias(list_alias_t *list_alias, char *new, char *cmd)
{
	alias_t *new_element;

	if ((list_alias != NULL) && (cmd != NULL)) {
		if (((new_element = malloc(sizeof(alias_t))) == NULL)
		|| ((new_element->alias = strdup(new)) == NULL)
		|| ((new_element->cmd = strdup(cmd)) == NULL))
			return (-1);
		restore_alias(new_element);
		epur_str(new_element->cmd);
		new_element->next = list_alias->first;
		new_element->prev = NULL;
		if (list_alias->first)
			list_alias->first->prev = new_element;
		else
			list_alias->last = new_element;
			list_alias->first = new_element;
	}
	return (0);
}

int del_alias(list_alias_t *list_alias, alias_t *element)
{
	if (element->next == NULL && element->prev == NULL)
		return (0);
	else if (element->next == NULL) {
		list_alias->last = element->prev;
		list_alias->last->next = NULL;
	}
	else if (element->prev == NULL) {
		list_alias->first = element->next;
		list_alias->first->prev = NULL;
	}
	else {
		element->next->prev = element->prev;
		element->prev->next = element->next;
	}
	free(element);
	return (0);
}

int my_unalias(list_alias_t *list_alias, char *cmd)
{
	alias_t *tmp;

	tmp = list_alias->first;
	while (tmp && cmd != NULL) {
		if (strcmp(cmd, tmp->alias) == 0)
			del_alias(list_alias, tmp);
		tmp = tmp->next;
	}
	return (0);
}

char *change_alias(char *cmd, list_alias_t *list_alias)
{
	alias_t *tmp;
	char *new_cmd;

	tmp = list_alias->first;
	new_cmd = cmd;
	while (tmp) {
		if (strncmp(cmd, tmp->alias, strlen(tmp->alias)) == 0) {
			if (cmd[strlen(tmp->alias)] == '\0'
			|| cmd[strlen(tmp->alias)] == ' ') {
				if (((new_cmd = my_catalloc(tmp->cmd,
					&cmd[strlen(tmp->alias)], NULL))
					!= NULL)) {
					free(cmd);
					 return (new_cmd);
				 }
				 return (NULL);
			 }
		 }
		 tmp = tmp->next;
	 }
	 return (new_cmd);
}
