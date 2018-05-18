/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** main.c
*/

#include "minishell.h"

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

char *read_line_cmd(void)
{
	char c = 0;
	char *buf;
	int i = 0;

	while (c != '\n') {
		c = getch_one_char(0);
		buf = realloc(buf, (i + 2) * sizeof(char));
		buf[i] = c;
		i = i + 1;
	}
	buf[i - 1] = '\0';
	return (buf);
}

int main(int __attribute__((unused)) ac, char __attribute__((unused)) *av[],
char *env[])
{
	char *buf = NULL;
	int quit = 0;

	while (quit != -1 && quit != 255) {
		my_putstr("$> ");
		buf = get_next_line(0);
		if (buf == NULL)
			break;
		quit = manage_multiple_commande(buf, &env);
		free(buf);
	}
	return ((quit == -1 || quit == 255) ? (0) : quit);
}