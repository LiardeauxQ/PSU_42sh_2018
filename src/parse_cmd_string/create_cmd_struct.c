/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** create_cmd_struct.c
*/

#include "minishell.h"

int find_separator(char *str_cmd, struct cmd_s *cmd);

void add_cmd_child(char *cmd, struct cmd_s *child, struct cmd_s *parent)
{
	child->separator = 0;
	child->cmd = my_strdup(cmd);
	child->argv = my_str_to_wordtab(cmd, " \t");
	child->redirection = check_if_redirection(child->argv);
	child->childs = NULL;
	child->parent = parent;
}

int split_separator_cmd(cmd_t *cmd, char *str_cmd, char *str_sep, int sep)
{
	char **split_cmd = my_str_to_wordtab_str(str_cmd, str_sep);
	int size = count_2d_array(split_cmd);
	int i = 0;

	if (split_cmd == NULL)
		return (-1);
	for (int j = 0 ; split_cmd[j] != NULL ; j++)
		split_cmd[i] = remove_useless_char(split_cmd[i], " \t");
	cmd->childs = malloc((size + 1) * sizeof(cmd_t));
	cmd->cmd = my_strdup(str_cmd);
	cmd->argv = NULL;
	while (split_cmd[i] != NULL) {
		if (find_separator(split_cmd[i], &cmd->childs[i]) == 0)
			add_cmd_child(split_cmd[i], &cmd->childs[i], cmd);
		i = i + 1;
	}
	cmd->childs[i].separator = -1;
	cmd->redirection = 0;
	cmd->separator = sep;
	destroy_2darray(split_cmd);
	return (0);
}

int find_separator(char *str_cmd, struct cmd_s *cmd)
{
	int separator = 0;
	int statu = 0;

	if (check_if_str_in_str(str_cmd, "&&") != -1 && separator == 0) {
		separator = AND_SEP;
		statu = split_separator_cmd(cmd, str_cmd, "&&", AND_SEP);
	}
	if (check_if_str_in_str(str_cmd, "|") != -1 && separator == 0) {
		if (check_if_str_in_str(str_cmd, "||") != -1 && separator == 0) {
			separator = OR_SEP;
			statu = split_separator_cmd(cmd, str_cmd, "||",
			OR_SEP);
		} else {
			separator = PIPE_SEP;
			statu = split_separator_cmd(cmd, str_cmd, "|",
			PIPE_SEP);
		}
	}
	if (statu == -1)
		return (-1);
	return (separator);
}

cmd_t *create_cmd_struct(char *str_cmd)
{
	int size = count_char_rec(str_cmd, ";");
	cmd_t *cmd = malloc((size + 1) * sizeof(cmd_t));
	char **split_cmd = my_str_to_wordtab(str_cmd, ";");
	int statu = 0;
	int i = 0;

	while (split_cmd[i] != NULL) {
		statu = find_separator(split_cmd[i], &cmd[i]);
		if (statu == 0)
			add_cmd_child(split_cmd[i], &cmd[i], NULL);
		i = i + 1;
	}
	cmd[i].separator = -1;
	destroy_2darray(split_cmd);
	return (cmd);
}

void display_cmd(cmd_t *cmd)
{
	if (cmd == NULL)
		return;
	printf("cmd\n");
	for (int i = 0 ; cmd[i].separator != -1 ; i++) {
		printf("%d . cmd : %s separator %d\n", i, cmd[i].cmd, cmd[i].separator);
		display_cmd(cmd[i].childs);
	}
}

void destroy_cmd(cmd_t *cmd)
{
	if (cmd == NULL)
		return;
	for (int i = 0 ; cmd[i].separator != -1 ; i++) {
		destroy_cmd(cmd[i].childs);
		if (cmd[i].cmd)
			free(cmd[i].cmd);
		if (cmd[i].argv)
			destroy_2darray(cmd[i].argv);
		if (cmd[i].childs)
			free(cmd[i].childs);
	}
}
