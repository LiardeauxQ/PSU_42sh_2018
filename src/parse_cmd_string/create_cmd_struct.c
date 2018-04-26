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
	child->argv = NULL;
	if (check_if_str_in_str(cmd, ">") != -1)
		child->argv = my_str_to_wordtab_no_supr(cmd, ">");
	if (check_if_str_in_str(cmd, "<") != -1)
		child->argv = my_str_to_wordtab_no_supr(cmd, "<");
	if (check_if_str_in_str(cmd, ">>") != -1)
		child->argv = my_str_to_wordtab_no_supr(cmd, ">>");
	if (check_if_str_in_str(cmd, "<<") != -1)
		child->argv = my_str_to_wordtab_no_supr(cmd, "<<");
	if (child->argv == NULL)
		child->argv = my_str_to_wordtab(cmd, " \t");
	else {
		for (int j = 0 ; child->argv[j] != NULL ; j++)
			child->argv[j] = remove_useless_char(child->argv[j],
				" \t");
	}
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
		split_cmd[j] = remove_useless_char(split_cmd[j], " \t");
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
	int sep = 0;
	int statu = 0;

	if (check_if_str_in_str(str_cmd, "&&") != -1 && sep == 0) {
		sep = AND_SEP;
		statu = split_separator_cmd(cmd, str_cmd, "&&", AND_SEP);
	}
	if (check_if_str_in_str(str_cmd, "|") != -1 && sep == 0) {
		if (check_if_str_in_str(str_cmd, "||") != -1 && sep == 0) {
			sep = OR_SEP;
			statu = split_separator_cmd(cmd, str_cmd, "||",
			OR_SEP);
		} else {
			sep = PIPE_SEP;
			statu = split_separator_cmd(cmd, str_cmd, "|",
			PIPE_SEP);
		}
	}
	if (statu == -1)
		return (-1);
	return (sep);
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
		printf("%d . cmd : %s separator %d\n", i, cmd[i].cmd,
		cmd[i].separator);
		if (cmd[i].argv != NULL) {
			for (int j = 0 ; cmd[i].argv[j] != NULL ; j++) {
				printf("argv : %s\n", cmd[i].argv[j]);
			}
		}
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
