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

int print_buffer(char *buf)
{
	static int last_size = 0;

	if (buf == NULL) {
		last_size = 0;
		return (1);
	}
	for (int i = 0 ; i < last_size ; i++)
		putstr_fd("\b \b", 0);
	putstr_fd(buf, 0);
	last_size = my_strlen(buf);
	return (0);
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

static int check_special_char(char const c, char *buf, int *i, int *pos)
{
	int quit = 0;
	int arrow = 0;

	if (c == 4)
		quit = 2;
	if (c == 27)
		arrow = check_arrow_key();
	if (arrow == 4) {
		*i = *i - 1;
		*pos = *pos - 1;
	}
	if (arrow != 0)
		return (1);
	if (*pos <= 3 && c >= 127) {
		quit = 3;
	} else if (c == 127) {
		*i = *i - 1;
		*pos = *pos - 1;
		putstr_fd(" \b\b ", 0);
		buf[*i] = '\0';
		quit = 1;
	}
	return (quit);
}

char *read_line_cmd(void)
{
	char c = 0;
	char *buf = NULL;
	int spe = 0;
	int pos = 3;
	int i = 0;

	while (c != '\n') {
		print_buffer(buf);
		c = getch_one_char(0);		
		spe = check_special_char(c, buf, &i, &pos);
		if (spe == 0 && c != '\n') {
			buf = realloc(buf, (i + 2) * sizeof(char));
			buf[i] = c;
			buf[i + 1] = '\0';
			i = i + 1;
			pos = pos + 1;
		} else if (spe == 2)
			return (NULL);
	}
	putchar_fd('\n', 0);
	return (buf);
}