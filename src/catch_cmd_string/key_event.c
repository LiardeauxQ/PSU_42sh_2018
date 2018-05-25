/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** key_event.c
*/

#include "minishell.h"

char getch_one_char(int fd)
{
	char buf = 0;
	struct termios ter = {0};
	fd = fileno(stdin);

	if (ioctl(fd, TCGETS, &ter) < 0)
		perror("tcsetattr()");
	ter.c_lflag &= ~ICANON;
	ter.c_lflag &= ~ECHO;
	ter.c_cc[VMIN] = 1;
	ter.c_cc[VTIME] = 0;
	if (ioctl(fd, TCSETS, &ter) < 0)
		perror("tcsetattr ICANON");
	if (read(fd, &buf, 1) < 0)
		perror("read()");
	ter.c_lflag |= ICANON;
	ter.c_lflag |= ECHO;
	if (ioctl(fd, TCSETSW, &ter) < 0)
		perror("tcsetattr ~ICANON");
	return (buf);
}

int check_arrow_key(void)
{
	char c = getch_one_char(0);

	if (c == 91) {
		c = getch_one_char(0);
		switch (c) {
			case 65:
				return (1);
			case 67:
				return (2);
			case 66:
				return (3);
			case 68:
				return (4);
		}
		if (c != 54 || c != 53)
			return (0);
		c = (c == 54) ? (3) : (1);
		if (getch_one_char(0) == 126)
			return (c);
	}
	return (0);
}

int check_arrow_key_event(stock_buffer_t *stk_buf)
{
	int arrow = 0;
	char *test[] = {"aze", "rty", "test", "encore des tests", NULL};
	static int a = 0;

	if (stk_buf->c == 27)
		arrow = check_arrow_key();
	if (arrow == 1 || arrow == 3) {
		a += ((arrow == 1) ? (1) : (-1));
		if (stk_buf->buf != NULL)
			free(stk_buf->buf);
		stk_buf->buf = my_strdup(test[a]);
	}
	if (arrow == 2 && stk_buf->pos < stk_buf->size) {
		stk_buf->pos += 1;
		print_arrow(67);
	} else if (arrow == 4 && stk_buf->pos > 0) {
		stk_buf->pos -= 1;
		print_arrow(68);
	}
	return (arrow);
}

static void print_back_line(stock_buffer_t *stk_buf, int cols)
{
	int delta = 0;

	putstr_fd("\b \b", 0);
	print_arrow(65);
	if (my_strlen(stk_buf->buf) <= cols) {
		delta = 3;
	}
	for (int i = 0 ; i < cols + delta ; i++)
		print_arrow(67);
}

int check_special_char(stock_buffer_t *stk_buf, int cols)
{
	int quit = 0;
	int arrow = 0;

	if (stk_buf->c == 4)
		quit = 2;
	if (stk_buf->pos + 3 <= 3 && stk_buf->c >= 127) {
		quit = 3;	
	} else if (stk_buf->c == 127) {
		stk_buf->pos = stk_buf->pos - 1;
		stk_buf->size = stk_buf->size - 1;
		if (my_strlen(stk_buf->buf) % cols == cols - 2)
			print_back_line(stk_buf, cols);
		stk_buf->buf = remove_char_in_buffer(stk_buf->buf,
		stk_buf->pos, 1);
		stk_buf->spe_buf[stk_buf->pos] = '\0';
		quit = 1;
	}
	if (check_tab_key(stk_buf, cols))
		quit = 1;
	return (quit);
}