/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_aliase.c
*/

#include "minishell.h"

void alias_getcontent(list_t *alias, char *str)
{
	char *key;
	char *cmd;
	list_t *tmp;

	if (my_strncmp("alias", str, 5) == 0) {
		str = str + 6;
		key = words_get(str, 1, " \t");
		str = str + strlen(key) + 1;
		while (*str == '\t' || *str == ' ')
			str = str + 1;
		if (*str != '\0') {
			cmd = my_strdup(str);
			if ((tmp = get_node_by_key(alias, key)) == NULL)
				list_add(alias, key, cmd);
		else
			tmp->content = cmd;
		}
	}
}

void alias_openfile(list_t *alias, char *file)
{
	int fd;
	char *tmp;

	if ((fd = open(file, O_RDONLY)) == -1) {
		my_puterror("Error when oppening file : ");
		my_puterror(file);
		my_putchar('\n');
	}
	else {
		while ((tmp = get_next_line(fd)) != NULL) {
			alias_getcontent(alias, tmp);
			free(tmp);
		}
	}
	close(fd);
}

char *alias_get(list_t *alias, char *key)
{
	list_t *tmp;

	tmp = alias->next;
	while (tmp != alias) {
		if (my_strcmp(tmp->key, key) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

void alias_initialize(list_t *alias)
{
	list_t *alias_tmp;

	alias_openfile(alias, "42rc");
	alias_tmp = alias->next;
	while (alias_tmp != alias)
		alias_tmp = alias_tmp->next;
}

char *alias_replace(list_t *alias, char *cmd)
{
	list_t *tmp_alias;
	list_t *test;
	char *tmp;
	int n = 0;

	tmp_alias = list_create();
	while (n < words_count(cmd, "&;|<")) {
		tmp = words_get(cmd, n + 1, "&;|<");
		list_add(tmp_alias, tmp, tmp);
		n++;
	}
	test = tmp_alias->next;
	while (test != tmp_alias) {
		tmp = words_get(test->content, 1, " \0");
		if (alias_get(alias, tmp) != NULL) {
			test->content = xreplace(test->content, tmp, alias_get(alias, tmp));
			cmd = xreplace(cmd, test->key, test->content);
		}
		test = test->next;
	}
	return (cmd);
}

int my_alias(mysh_t *sh, char **cmd)
{
	char *str;
	list_t *tmp;

	if (cmd[1] != NULL && cmd[2] != NULL) {
		if ((str = tab_to_str(cmd)) != NULL)
			alias_getcontent(sh->alias, str);
	} else if (count_dab(cmd) == 1) {
		tmp = sh->alias->next;
		while (tmp != sh->alias) {
			printf("%s\t%s\n", tmp->key, tmp->content);
			tmp = tmp->next;
		}
	}
	else
		return (-1);
	return (1);
}

int my_unalias(mysh_t *sh, char **cmd)
{
	list_t *tmp;

	if (cmd[1] != NULL) {
		tmp = sh->alias->next;
		while (tmp != sh->alias) {
			if (match(tmp->key, cmd[1]) == 1)
			list_delete_node(tmp);
			tmp = tmp->next;
		}
	}
	else {
		my_puterror("unalias: Too few arguments.\n");
		return (-1);
	}
	return (1);
}
