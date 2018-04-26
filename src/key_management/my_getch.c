/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** my_getch.c
*/

#include "minishell.h"

char my_getch(void)
{
	char buf = 0;
	struct termios ter = {0};

	if (ioctl(0, TCGETS, &ter) < 0)
		perror("tcsetattr()");
	ter.c_lflag &= ~ICANON;
	ter.c_lflag &= ~ECHO;
	ter.c_cc[VMIN] = 1;
	ter.c_cc[VTIME] = 0;
	if (ioctl(0, TCSETS, &ter) < 0)
		perror("tcsetattr ICANON");
	if (read(0, &buf, 1) < 0)
		perror("read()");
	ter.c_lflag |= ICANON;
	ter.c_lflag |= ECHO;
	if (ioctl(0, TCSETSW, &ter) < 0)
		perror("tcsetattr ~ICANON");
	return (buf);
}

void manage_arrow(void)
{
	quit = my_getch();
	if (quit == '\033') {
		quit = my_getch();
		switch (my_getch()) {
			case 'A':
				printf("arrow up\n");
				break;
			case 'B':
				printf("arrow down\n");
				break;
			case 'C':
				printf("arrow right\n");
				break;
			case 'D':
				printf("arrow left\n");
				break;
		}
	}
}
