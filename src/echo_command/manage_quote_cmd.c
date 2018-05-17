/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_quote_cmd.c
*/

#include "minishell.h"

void check_if_cmd_quote(char *cmd, echo_cmd_t *split_cmd)
{
	int quote = 0;
	int j = 0;
	int k = 0;
	int size = 0;

	for (int i = 0 ; i < my_strlen(cmd) ; i++) {
		if (split_cmd[j + 1].str != NULL 
		&& split_cmd[j].str[k] == '\0') {
			j = j + 1;
			k = 0;
		}
		k = k + 1;	
		if (cmd[i] == 34) {
			i = i + 1;
			size = i;
			(quote == 0) ? (quote = 1) : (quote = 0);
		}
		if (quote == 1 && (k + size) >= i 
		&& k <= (size + my_strlen(split_cmd[j].str)))
			split_cmd[j].quote = 1;
	}
}

static echo_cmd_t *split_echo_cmd(char *str, char *c)
{
	char *tmp = str;
	char *saveptr = NULL;
	char *token = strtok_r(tmp, c, &saveptr);
	echo_cmd_t *split_cmd = NULL;
	int size = 1;

	while (token != NULL) {	
		split_cmd = realloc(split_cmd, (size + 1) * sizeof(echo_cmd_t));
		split_cmd[size - 1].str = my_strdup(token);
		split_cmd[size - 1].quote = 0;
		tmp = NULL;
		token = strtok_r(tmp, c, &saveptr);
		size = size + 1;
	}
	split_cmd[size - 1].quote = -1;
	split_cmd[size - 1].str = NULL;
	return (split_cmd);
}

static int count_char_in_str(char *str, char c)
{
	int size = 0;

	for (int i = 0 ; str[i] != '\0' ; i++)
		if (str[i] == c)
			size = size + 1;
	return (size);
}

echo_cmd_t *manage_quote_cmd(char *cmd)
{
	char *delim = "\"";
	char *sub_delim = " \t";
	echo_cmd_t *split_cmd = NULL;
	char *tmp = my_strdup(cmd);
	int quote = count_char_in_str(cmd, 34);
	
	if (quote % 2 != 0)
		return (NULL);
	if (quote == 0)
		delim = sub_delim;
	split_cmd = split_echo_cmd(tmp, delim);
	if (quote == 0)
		return (split_cmd);
	check_if_cmd_quote(cmd, split_cmd);
	for (int i = 0 ; split_cmd[i].quote != -1 ; i++) {
		if (split_cmd[i].quote != 1)
			split_cmd[i].str = 
			remove_useless_char(split_cmd[i].str, " \t");
	}
	free(tmp);
	return (split_cmd);
}
