/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** recup_echo_argument.c
*/

#include "minishell.h"

int manage_control_char(char control_char[], int *i)
{
	int ascii_value = 0;
	int base = 8;

	if (control_char[0] == 'x' || control_char[0] == 'X')
		base = 16;
	ascii_value = convert_base_to_decimal(control_char, base);
	*i = *i + 1;
	if (ascii_value != 0) {
		switch (control_char[0]) {
			case '0': return (0);
			case 'a': return (7);
			case 'b': return (8);
			case 't': return (9);
			case 'n': return (10);
			case 'v': return (11);
			case 'f': return (12);
			case 'r': return (13);
		}
	}
	*i = *i + 2;
	return (ascii_value);
}

void print_echo_str(char *str)
{
	char spe_char[4] = {0};

	for (int i = 0 ; i < my_strlen(str) ; i++) {
		if (str[i] == '\\') {
			spe_char[0] = str[i + 1];
			spe_char[1] = str[i + 2];
			spe_char[2] = str[i + 3];
			my_putchar(manage_control_char(spe_char, &i));
		} else
			my_putchar(str[i]);
	}
}

int choose_echo_option(echo_cmd_t *sp_cmd, int *i)
{
	char **first_cell = my_str_to_wordtab(sp_cmd[0].str, " \t");
	int option = 0;
	int alone_echo = 0;

	if (count_2d_array(first_cell) == 1)
		alone_echo = 1;
	while (alone_echo == 1 && sp_cmd[*i].str != NULL
	&& (my_strcmp("-e", sp_cmd[*i].str) || my_strcmp("-E", sp_cmd[*i].str)
	|| my_strlen(sp_cmd[*i].str) == 0)) {
		if (my_strcmp(sp_cmd[*i].str, "-E"))
			option = 1;
		*i = *i + 1;
	}
	for (int j = 1 ; alone_echo == 0 && first_cell[j] != NULL
	&& (my_strcmp("-e", first_cell[j])
	|| my_strcmp("-E", first_cell[j])) ; j++) {
		if (my_strcmp(first_cell[j], "-E"))
			option = 1;
	}
	destroy_2darray(first_cell);
	return (option);
}

int execute_echo_command(cmd_t *cmd)
{
	echo_cmd_t *split_cmd = manage_quote_cmd(cmd->cmd);
	int quite = 0;
	int i = 1;
	int interpretation = choose_echo_option(split_cmd, &i);
	int size = 0;

	if (split_cmd == NULL)
		quite = 1;
	for (int j = 0 ; split_cmd[j].str != NULL ; j++)
		size = size + 1;
	while (i < size) {
		if (interpretation == 0)
			print_echo_str(split_cmd[i].str);
		else
			my_putstr(split_cmd[i].str);
		if (my_strlen(split_cmd[i].str) == 0)
			my_putchar(' ');
		i = i + 1;
	}
	my_putchar('\n');
	return (quite);
}
