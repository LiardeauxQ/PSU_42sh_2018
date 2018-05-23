/*
** EPITECH PROJECT, 2018
** manage inibitors.c
** File description:
** 42sh
*/

#include "manage_multiple_command.h"

int	count_inhib(char *cmd)
{
	int	res = 0;

	for (int i = 0; cmd[i] != '\0'; i++)
		if (cmd[i] == '\\')
			++res;
	return (res);
}

/*int	check_tab(char c)
{
	if (c == '\ ' || c == '\'' || c == '\"' || c == '\\')
		return (0);
	else if (c == '\?' || c == '\0' || c == '\a' || c == '\b' ||
		c == '\f' || c == '\n' || c == '\r' || c == '\t' ||
		c == '\v')
		return (1);
}

char	*ignore_inhib(char *cmd)
{
	while (*cmd)
		if (check_tab(*cmd) == 0)
			++(*cmd);
		else
			(*cmd) += 1;
	return (cmd);
}
*/

char	*basic_inhib(char *cmd, char c, int i)
{
	if (c != '\0')
		cmd[i] = c;
	while (cmd[i] != '\0') {
		cmd[i] = cmd[i + 1];
		++i;
	}
	return (cmd);
}

char	*spaces_inhib(char *cmd)
{
	for (int i = 0; cmd[i] != '\0'; i++) {
		if (cmd[i] == '\\' && cmd[i + 1] == ' ')
			cmd = basic_inhib(cmd, 32, i);
		if (cmd[i] == '\\' && cmd[i + 1] == '\"')
			cmd = basic_inhib(cmd, 34, i);
		if (cmd[i] == '\\' && cmd[i + 1] == '\'')
			cmd = basic_inhib(cmd, 39, i);
		if (cmd[i] == '\\')
			cmd = basic_inhib(cmd, 0, i);
		if (cmd[i] == '\\' && cmd[i + 1] == '\\')
			cmd = basic_inhib(cmd, 92, i);
	}
	return (cmd);
}

char	*replace_ascii_inhib(char *cmd)
{
	for (int i = 0; cmd[i] != '\0'; i++) {
		if (cmd[i] == '\\' && cmd[i + 1] == 'a')
			cmd = basic_inhib(cmd, 7, i);
		if (cmd[i] == '\\' && cmd[i + 1] == 'b')
			cmd = basic_inhib(cmd, 8, i);
		if (cmd[i] == '\\' && cmd[i + 1] == 't')
			cmd = basic_inhib(cmd, 9, i);
		if (cmd[i] == '\\' && cmd[i + 1] == 'n')
			cmd = basic_inhib(cmd, 10, i);
		if (cmd[i] == '\\' && cmd[i + 1] == 'v')
			cmd = basic_inhib(cmd, 11, i);
		if (cmd[i] == '\\' && cmd[i + 1] == 'f')
			cmd = basic_inhib(cmd, 12, i);
		if (cmd[i] == '\\' && cmd[i + 1] == 'r')
			cmd = basic_inhib(cmd, 13, i);
	}
	return (cmd);
}

char	*manage_inhibitors(char *cmd)
{
	char	**tab = NULL;
	char	inhib[4] = {' ', '"', '\'', '\\'};

	if (count_inhib(cmd) == 0)
		return (cmd);
	for (int i = 0; i < 4; i++) {
		tab = my_str_to_back_tab(cmd, inhib[i]);
//		for (int j = 0; tab[j] != NULL; j++)
//			printf("%s\n", tab[j]);
		my_free_tab(tab);
	}
//	cmd = ignore_inhib(cmd);
//	cmd = replace_ascii_inhib(cmd);
//	cmd = spaces_inhib(cmd);
	return (cmd);
}
