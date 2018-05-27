/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** movement_history.c
*/

#include "minishell.h"

char **open_history(void)
{
	int fd = open(".42sh_history", O_RDONLY);
	int size = 0;
	int hist_size = 1;
	char *buf = NULL;
	char **split_hist = NULL;
	char **history = NULL;

	if (fd == -1)
		return (NULL);
	while ((buf = get_next_line(fd)) != NULL) {
		split_hist = my_str_to_wordtab(buf, "\t");
		size = count_2d_array(split_hist);
		history = realloc(history, (hist_size + 1) * sizeof(char *));
		history[hist_size - 1] = strdup(split_hist[size - 1]);
		hist_size += 1;
		destroy_2darray(split_hist);
		free(buf);
	}
	if (history)
		history[hist_size - 1] = NULL;
	return (history);
}

void print_new_history_cmd(stock_buffer_t *stk)
{
	for (int j = 0 ; j < my_strlen(stk->buf) ; j++) {
		if (stk->spe_buf[j] != -1)
			putchar_fd(stk->spe_buf[j], 0);
		putchar_fd(stk->buf[j], 0);
	}
	print_buffer(stk, 1);
}

void move_cmd_history(stock_buffer_t *stk, char *history)
{
	if (history == 0x0)
		return;
	if (stk->buf != NULL) {
		for (int i = 0 ; stk->buf[i] != '\0' ; i++)
			putstr_fd("\b \b", 0);
	}
	if (stk->buf != 0x0) {
		free(stk->buf);
		free(stk->spe_buf);
	}
	stk->buf = strdup(history);
	stk->spe_buf = malloc(my_strlen(stk->buf));
	stk->spe_buf = memset(stk->spe_buf, -1, my_strlen(stk->buf));
	stk->spe_buf[my_strlen(stk->buf)] = '\0';
	stk->size = my_strlen(stk->buf);
	stk->pos = stk->size;
	print_new_history_cmd(stk);
}
