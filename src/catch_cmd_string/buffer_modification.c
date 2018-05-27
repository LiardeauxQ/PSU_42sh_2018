/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** buffer_modification.c
*/

#include "minishell.h"

int clean_window_buffer(stock_buffer_t *stk_buf, int *j, int reset)
{
	static int last_size = 0;

	if (stk_buf == 0x0 || stk_buf->buf == 0x0) {
		last_size = 0;
		*j = 0;
		return (1);
	}
	if (reset == 0 && stk_buf->pos == stk_buf->size) {
		for (int i = 0 ; i < last_size
		- my_strlen(stk_buf->buf) ; i++) {
			putstr_fd("\b \b", 0);
			*j = *j - 1;
		}
	} else if (reset == 0)
		*j = stk_buf->pos - 1;
	last_size = my_strlen(stk_buf->buf);
	return (0);
}

int print_buffer(stock_buffer_t *stk_buf, int reset)
{
	static int j = 0;

	if (clean_window_buffer(stk_buf, &j, reset))
		return (1);
	if (reset == 1) {
		j = my_strlen(stk_buf->buf);
		return (0);
	}
	if (j < 0)
		j = 0;
	while (j < my_strlen(stk_buf->buf)) {
		if (stk_buf->spe_buf[j] != -1)
			putchar_fd(stk_buf->spe_buf[j], 0);
		putchar_fd(stk_buf->buf[j], 0);
		j = j + 1;
	}
	for (int a = 0 ; a < stk_buf->size - stk_buf->pos ; a++)
		print_arrow(68);
	return (0);
}

static char *add_char_in_buffer(char *buffer, char c, int cursor_pos, int size)
{
	char tmp1 = 0;
	char tmp2 = 0;
	int buf_size = my_strlen(buffer);
	int i = 0;

	tmp1 = buffer[cursor_pos];
	buffer[cursor_pos] = c;
	if (size == cursor_pos) {
		buffer[cursor_pos + 1] = tmp1;
		return (buffer);
	}
	for (i = cursor_pos + 1 ; i < buf_size + 1 ; i++) {
		tmp2 = buffer[i];
		buffer[i] = tmp1;
		tmp1 = tmp2;
	}
	buffer[i] = tmp1;
	return (buffer);
}

char *remove_char_in_buffer(char *buffer, int current_pos, int move)
{
	int i = current_pos;
	int size = my_strlen(buffer);

	if (i <= 0)
		i = 0;
	while (i < size) {
		buffer[i] = buffer[i + 1];
		i = i + 1;
	}
	if (current_pos + 1 != size && move == 1) {
		for (int k = current_pos ; k < size ; k++)
			print_arrow(67);
		if (current_pos <= 1)
			current_pos = 1;
		for (int j = current_pos - 2 ; j < size ; j++)
			putstr_fd("\b \b", 0);
	}
	return (buffer);
}

void fill_buf(stock_buffer_t *stk_buf, int cols)
{
	stk_buf->buf = realloc(stk_buf->buf, (stk_buf->size + 2));
	stk_buf->spe_buf = realloc(stk_buf->spe_buf, (stk_buf->size + 2));
	stk_buf->buf[stk_buf->size] = '\0';
	stk_buf->spe_buf[stk_buf->size] = '\0';
	if (stk_buf->c == '\n')
		stk_buf->buf[stk_buf->size] = '\0';
	else
		stk_buf->buf = add_char_in_buffer(stk_buf->buf, stk_buf->c,
		stk_buf->pos, stk_buf->size);
	stk_buf->spe_buf[stk_buf->pos] = -1;
	if (my_strlen(stk_buf->buf) % cols == cols - 1)
		stk_buf->spe_buf[stk_buf->pos] = '\n';
	stk_buf->pos = stk_buf->pos + 1;
	stk_buf->size = stk_buf->size + 1;
}
