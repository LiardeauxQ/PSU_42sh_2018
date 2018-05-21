/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** catch_cmd_string.h
*/

#ifndef CATCH_CMD_STRING_H_
#define CATCH_CMD_STRING_H_

typedef struct stock_buffer_s {
	char c;
	int pos;
	int size;
	char *buf;
	char *spe_buf;
} stock_buffer_t;

char *read_line_cmd(void);

#endif /* CATCH_CMD_STRING_H_ */