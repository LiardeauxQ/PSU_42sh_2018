/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** read_cmd_string.c
*/

#include "minishell.h"

void putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int putstr_fd(char *str, int fd)
{
	if (str == NULL)
		return (1);
	write(fd, str, my_strlen(str));
	return (0);
}

void print_arrow(char arrow_type)
{
	putchar_fd(27, 0);
	putchar_fd(91, 0);
	putchar_fd(arrow_type, 0);
}

char *read_line_cmd(int fd)
{
	int spe = 0;
	int arrow = 0;
	int cols = 0;
	char **history = open_history();
	stock_buffer_t stk_buf = {0, 0, 0, count_2d_array(history) - 1,  NULL, NULL};

	tgetent(NULL, getenv("TERM"));
	cols = tgetnum("co") - 2;
	while (stk_buf.c != '\n') {
		if (arrow == 0)
			print_buffer(&stk_buf);
		stk_buf.c = getch_one_char(fd);
		spe = check_special_char(&stk_buf, cols);
		arrow = check_arrow_key_event(&stk_buf, history);
		if (spe == 0 && arrow == 0) {
			fill_buf(&stk_buf, cols);
		} else if (spe == 2) {
			stk_buf.buf = NULL;
			break;
		}
	}
	putchar_fd('\n', 0);
	destroy_2darray(history);
	return (stk_buf.buf);
}
