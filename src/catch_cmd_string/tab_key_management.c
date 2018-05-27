/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** tab_key_management.c
*/

#include "minishell.h"

static char *update_spe_buf_cmd(char const *buf, int cols)
{
	char *spe_buf = malloc((strlen(buf) + 1) * sizeof(char));

	check_malloc(spe_buf);
	for (int i = 0 ; buf[i] != '\0' ; i++) {
		if (my_strlen(buf) % cols == cols - 1)
			spe_buf[i] = '\n';
		else {
			spe_buf[i] = -1;
		}
	}
	return (spe_buf);
}

static void manage_current_dir_tab(stock_buffer_t *stk_buf, list_t *cmd_list)
{
	int slash_pos = 0;
	int delta = 0;
	int tmp = 0;

	for (int i = my_strlen(stk_buf->buf) ; i >= 0 && stk_buf->buf[i] != '/' && stk_buf->buf[i] != ' ' ; i--)
		slash_pos = i;

	stk_buf->buf = realloc(stk_buf->buf, my_strlen(stk_buf->buf) + my_strlen(cmd_list->data) + 1);
	tmp = my_strlen(stk_buf->buf) - slash_pos;
	if (tmp < my_strlen(cmd_list->data))
		stk_buf->buf = strcat(stk_buf->buf, cmd_list->data + tmp);
}

static void update_buf_cmd_if_tab(stock_buffer_t *stk_buf, int cols, int size)
{
	list_t *cmd_list = NULL;
	int list_size = 0;

	cmd_list = find_cmd_completion(stk_buf->buf, stk_buf->pos, size - 1);
	list_size = count_list_size(cmd_list);
	if (list_size > 1) {
		putchar_fd('\n', 0);
		print_tab_command(cmd_list, cols - 20);
		my_putstr("\n$> ");
		putstr_fd(stk_buf->buf, 0);
	} else if (list_size == 1) {
		manage_current_dir_tab(stk_buf, cmd_list);		
		stk_buf->spe_buf = update_spe_buf_cmd(stk_buf->buf, cols);
		stk_buf->size = strlen(stk_buf->buf);
		stk_buf->pos = stk_buf->size;
	}
	destroy_list(cmd_list);
}

int check_tab_key(stock_buffer_t *stk_buf, int cols)
{
	char **split_cmd = NULL;
	int size = 0;

	if (stk_buf->buf == NULL)
		return (0);
	if (my_strlen(stk_buf->buf) != 0) {
		split_cmd = my_str_to_wordtab(stk_buf->buf, " \t");
		size = count_2d_array(split_cmd);
		destroy_2darray(split_cmd);
	}
	if (stk_buf->c == '\t') {
		update_buf_cmd_if_tab(stk_buf, cols, size);
		return (1);
	}
	return (0);
}
