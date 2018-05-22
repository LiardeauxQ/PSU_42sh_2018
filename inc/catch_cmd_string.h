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


/*read_cmd_string.c */

void putchar_fd(char c, int fd);
int putstr_fd(char *str, int fd);
void print_arrow(char arrow_type);
char *read_line_cmd(void);

/* buffer_modification.c */

int print_buffer(stock_buffer_t *stk_buf);
void fill_buf(stock_buffer_t *stk_buf, int cols);
char *remove_char_in_buffer(char *buffer, int current_pos, int move);

/* key_event.c */

int check_arrow_key_event(stock_buffer_t *stk_buf);
int check_arrow_key(void);
char getch_one_char(int fd);
int check_special_char(stock_buffer_t *stk_buf, int cols);

#endif /* CATCH_CMD_STRING_H_ */