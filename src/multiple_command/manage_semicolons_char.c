/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_semicolons_char.c
*/

#include "minishell.h"

int check_if_special_str(char **split_cmd, char *c)
{
	if (split_cmd == NULL || c == NULL)
		return (-1);
	for (int i = 0 ; split_cmd[i] != NULL ; i++) {
		if (my_strcmp(c, split_cmd[i]) == 1)
			return (i);
	}
	return (-1);
}

static char **stock_cmd(char *cmd, int size)
{
	char **stock_tmp = NULL;
	int i = 0;
	int j = 0;
	int k = 0;

	stock_tmp = malloc((size + 1) * sizeof(char *));
	for (int a = 0 ; a < size ; a++)
		stock_tmp[a] = malloc(my_strlen(cmd) + 1);
	while (j < my_strlen(cmd)) {
		stock_tmp[i][k++] = cmd[j];
		j = j + 1;
		if (cmd[j] == ';') {
			stock_tmp[i][k] = '\0';
			j = j + 1;
			i = i + 1;
			k = 0;
		}
	}
	stock_tmp[i][k] = '\0';
	stock_tmp[i + 1] = NULL;
	return (stock_tmp);
}

static char ***split_cmd_if_semicolons(char *cmd)
{
	int size = 1;
	char **stock_tmp = NULL;
	char ***split_cmd = NULL;

	if (cmd == NULL)
		return (NULL);
	for (int i = 0 ; cmd[i] != '\0' ; i++)
		if (cmd[i] == ';')
			size = size + 1;
	stock_tmp = stock_cmd(cmd, size);
	split_cmd = malloc((size + 1) * sizeof(char *));
	check_malloc(stock_tmp);
	for (int c = 0 ; c < size ; c++)
		split_cmd[c] = my_str_to_wordtab(stock_tmp[c], " \t");
	split_cmd[size] = NULL;
	destroy_2darray(stock_tmp);
	return (split_cmd);
}

char **remove_needless_char(char **cmd)
{
	int i = 0;
	int j = 0;

	if (cmd == NULL)
		return (NULL);
	while (cmd[i] != NULL && j == 0) {
		if ((j = my_strlen(cmd[i])) != 0)
			break;
		i = i + 1;
	}
	while (cmd[i] != NULL) {
		cmd[i][j] = '\0';
		j = j - 1;
		if (j == -1 || (cmd[i][j] != ' ' && cmd[i][j] != '\t')) {
			i = i + 1;
			j = my_strlen(cmd[i]);
		}
	}
	return (cmd);
}

int manage_semicolons(char *cmd, char ***env)
{
	char ***argv = NULL;
	char **nw_cmd = NULL;
	int type = 0;
	int quit = 0;
	int i = 0;

	if ((argv = split_cmd_if_semicolons(cmd)) == NULL
	|| (nw_cmd = remove_needless_char(my_str_to_wordtab(cmd, ";"))) == NULL)
		return (-1);
	while (argv[i] != NULL && nw_cmd[i] != NULL && quit >= 0) {
		if (check_if_special_str(argv[i], "|") != -1) {
			quit = manage_pipe(nw_cmd[i], argv[i], env);
		} else if ((type = check_if_redirection(argv[i])) != 0) {
			quit = manage_redirection(nw_cmd[i], env, type, NULL);
		} else
			quit = check_one_command(nw_cmd[i], argv[i], env);
		i = i + 1;
	}
	destroy_2darray(nw_cmd);
	destroy_3darray(argv);
	return (quit);
}
