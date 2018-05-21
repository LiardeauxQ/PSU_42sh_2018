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

char getch_one_char(int fd)
{
	char buf = 0;
	struct termios ter = {0};

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

int print_buffer(stock_buffer_t *stk_buf)
{
	static int last_size = 0;
	static int j = 0;

	if (stk_buf->buf == NULL) {
		last_size = 0;
		j = 0;
		return (1);
	}
	for (int i = 0 ; i < last_size - my_strlen(stk_buf->buf) ; i++) {
		putstr_fd("\b \b", 0);
		j = j - 1;
	}
	while (j < my_strlen(stk_buf->buf)) {
		if (stk_buf->spe_buf[j] != -1)
			putchar_fd(stk_buf->spe_buf[j], 0);
		putchar_fd(stk_buf->buf[j], 0);
		j = j + 1;
	}
	last_size = my_strlen(stk_buf->buf);
	return (0);
}

void print_arrow(char arrow_type)
{
	putchar_fd(27, 0);
	putchar_fd(91, 0);
	putchar_fd(arrow_type, 0);
}

int check_arrow_key(void)
{
	char c = getch_one_char(0);

	if (c == 91) {
		switch (getch_one_char(0)) {
			case 65:
				return (1);
			case 67:
				return (2);
			case 66:
				return (3);
			case 68:
				return (4);
		}
	}
	return (0);
}

static int check_arrow_key_event(stock_buffer_t *stk_buf)
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
	if (arrow == 2) {
		stk_buf->pos += 1;
		print_arrow(67);
	} else if (arrow == 4) {
		stk_buf->pos -= 1;
		print_arrow(68);
	}
	return (arrow);
}

void print_back_line(stock_buffer_t *stk_buf, int cols)
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

static int check_special_char(stock_buffer_t *stk_buf, int cols)
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
		stk_buf->buf[stk_buf->pos] = '\0';
		stk_buf->spe_buf[stk_buf->pos] = '\0';
		quit = 1;
	}
	return (quit);
}

int add_char_in_buffer(char *buffer, char c, int cursor_pos)
{
	char tmp = 0;

	tmp = buffer[cursor_pos - 3];
	return (0);
}

void fill_buf(stock_buffer_t *stk_buf, int cols)
{
	stk_buf->buf = realloc(stk_buf->buf, (stk_buf->size + 2));
	stk_buf->spe_buf = realloc(stk_buf->spe_buf, (stk_buf->size + 2));
	if (stk_buf->c == '\n')
		stk_buf->buf[stk_buf->pos] = '\0';
	else
		stk_buf->buf[stk_buf->pos] = stk_buf->c;
	stk_buf->buf[stk_buf->pos + 1] = '\0';
	stk_buf->spe_buf[stk_buf->pos] = -1;
	if (my_strlen(stk_buf->buf) % cols == cols - 1)
		stk_buf->spe_buf[stk_buf->pos] = '\n';
	stk_buf->spe_buf[stk_buf->pos + 1] = '\0';
	stk_buf->pos = stk_buf->pos + 1;
	stk_buf->size = stk_buf->size + 1;
}

char *read_line_cmd(void)
{
	stock_buffer_t stk_buf = {0, 0, 0, NULL, NULL};
	int spe = 0;
	int arrow = 0;
	int i = 0;

	tgetent(NULL, getenv("TERM"));
	int cols = tgetnum("co") - 2;
	while (stk_buf.c != '\n') {
		print_buffer(&stk_buf);
		stk_buf.c = getch_one_char(0);
		spe = check_special_char(&stk_buf, cols);
		arrow = check_arrow_key_event(&stk_buf);
		if (spe == 0 && arrow == 0) {
			fill_buf(&stk_buf, cols);
		} else if (spe == 2) {
			stk_buf.buf = NULL;
			break;
		}
	}
	putchar_fd('\n', 0);
	return (stk_buf.buf);
}