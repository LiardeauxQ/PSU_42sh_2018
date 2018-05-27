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
	int hist_pos;
	char *buf;
	char *spe_buf;
} stock_buffer_t;

/*read_cmd_string.c */

void putchar_fd(char c, int fd);
int putstr_fd(char *str, int fd);
void print_arrow(char arrow_type);
char *read_line_cmd(int fd);

/* buffer_modification.c */

int print_buffer(stock_buffer_t *stk_buf, int reset);
void fill_buf(stock_buffer_t *stk_buf, int cols);
char *remove_char_in_buffer(char *buffer, int current_pos, int move);

/* key_event.c */

int check_arrow_key_event(stock_buffer_t *stk_buf, char **history);
int check_arrow_key(void);
char getch_one_char(int fd);
int check_special_char(stock_buffer_t *stk_buf, int cols);

/* cmd_operation.c */

list_t *add_cmd_to_list(char const *dirname, char const *cmd, list_t *cmd_list);
char *remove_cmd_dir_path(char *cmd);
char *add_dir_to_path(char *cmd);

/* order_cmd_list.c */

list_t *order_list(list_t *cmd_list);
int compare_str_alpha(list_t *list);

/* tab_completion.c */

list_t *open_dir_for_comparaison(char const *dirname, char const *str);
int check_cmd_already_in(list_t *cmd_list, char const *cmd);
void print_tab_command(list_t *list, int term_size);
list_t *find_cmd_completion(char *cmd, int pos);

/* tab_key_management.c */

int check_tab_key(stock_buffer_t *stk_buf, int cols);

/* movement_history.c */

char **open_history(void);
void move_cmd_history(stock_buffer_t *stk_buf, char *history);

#endif /* CATCH_CMD_STRING_H_ */