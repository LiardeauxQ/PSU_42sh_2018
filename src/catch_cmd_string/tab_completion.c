/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** tab_completion.c
*/

#include "minishell.h"

list_t *open_dir_for_comparaison(char const *dirname, char const *str)
{
	DIR *dir = opendir(dirname);
	struct dirent *dirent = 0x0;
	list_t *list = 0x0;

	if (dir == 0x0)
		return (0x0);
	while ((dirent = readdir(dir)) != 0x0) {
		if (strncmp(str, dirent->d_name, my_strlen(str)) == 0
		|| my_strlen(str) == 0)
			push(&list, dirent->d_name);
	}
	closedir(dir);
	return (list);
}

int check_cmd_already_in(list_t *cmd_list, char const *cmd)
{
	int already_in = 0;

	if (cmd_list == 0x0)
		return (already_in);
	for (list_t *tmp = cmd_list ; tmp != 0x0 ; tmp = tmp->next) {
		if (strcmp(tmp->data, cmd) == 0)
			already_in += 1;
	}
	return (already_in);
}

list_t *add_cmd_to_array(char const *dirname, char const *cmd, list_t *cmd_list)
{
	list_t *list = 0x0;

	list = open_dir_for_comparaison(dirname, cmd);
	if (list == 0x0)
		return (cmd_list);
	for (list_t *tmp = list ; tmp != 0x0 ; tmp = tmp->next) {
		if (check_cmd_already_in(cmd_list, tmp->data) == 0)
			push(&cmd_list, tmp->data);
	}
	destroy_list(list);
	return (cmd_list);
}

char *cut_cmd(char *cmd, int cursor)
{
	char *str_cut = malloc((cursor + 1) * sizeof(char));
	int i = 0;
	int j = 0;

	if (strlen(cmd) >= 2 && cmd[0] == '.' && cmd[1] == '/')
		i = 2;
	while (i < cursor) {
		str_cut[j] = cmd[i++];
		j = j + 1;
	}
	str_cut[j] = '\0';
	return (str_cut);
}

char *remove_cmd_dir_path(char *cmd)
{
	unsigned int delta = 0;

	for (int i = 0 ; cmd[i] != '\0' && cmd[i] != '/' ; i++)
		delta += 1;
	if (delta != strlen(cmd))
		cmd = cmd + delta + 1;
	return (cmd);
}

char *add_dir_to_path(char *pwd, char *cmd)
{
	int j = 0;
	int size = 0;
	char *new_pwd = strdup(pwd);

	if (count_char_rec(cmd, "/") - 1 == 0)
		return (new_pwd);
	size = my_strlen(new_pwd);
	new_pwd = realloc(new_pwd, size + 2);
	new_pwd = strcat(new_pwd, "/");
	j = strlen(new_pwd);
	size += strlen(cmd) + 1;
	new_pwd = realloc(new_pwd, size + 1);
	for (int i = 0 ; cmd[i] != '\0' && cmd[i] != '/' ; i++) {
		new_pwd[j] = cmd[i];
		j = j + 1;
	}
	new_pwd[j] = '\0';
	return (new_pwd);
}

int compare_str_alpha(list_t *list)
{
	for (int i = 0 ; list->data[i] != '\0'
	&& list->next->data[i] != '\0' ; i++) {
		if (list->data[i] > list->next->data[i])
			return (1);
	}
	return (0);
}

list_t *order_array(list_t *cmd_list)
{
	list_t *stock = NULL;
	int order = 0;

	if (cmd_list == NULL)
		return;
	for (list_t *tmp = cmd_list ; tmp->next != NULL ; tmp = tmp->next) {
		if (compare_str_alpha(tmp))
			swap(&tmp, &tmp->next);
	}
	my_putchar('\n');
	print_list(cmd_list);
	my_putchar('\n');
	for (list_t *tmp = cmd_list ; tmp->next != NULL ; tmp = tmp->next)
		if (compare_str_alpha(tmp))
			order = 1;
	if (order == 1)
		return (order_array(cmd_list));
	return (cmd_list);
}

void print_tab_command(char **tab_cmd, int term_size)
{
	int size = 0;
	int tmp_size = 0;
	int nb_cmd = 0;
	int cmd = -1;

	for (int i = 0 ; tab_cmd[i] != NULL ; i++) {
		tmp_size = strlen(tab_cmd[i]);
		if (tmp_size > size)
			size = tmp_size;	
	}
	nb_cmd = (int)(term_size / size);
	for (int j = 0 ; tab_cmd[j] != NULL ; j++) {
		cmd++;
		if (cmd == nb_cmd) {
			my_putchar('\n');
			cmd = 0;
		}
		my_putstr(tab_cmd[j]);
		for (int k = 0 ; k < (size - strlen(tab_cmd[j]) + 1) ; k++)
			my_putchar(' ');
	}
}

int find_cmd_completion(char *cmd, int cursor, int pos)
{
	char *tmp_str = NULL;
	char *path = getenv("PATH");
	char *pwd = getenv("PWD");
	char **split_path = my_str_to_wordtab(path, ":");
	list_t *cmd_list = 0x0;
	char *tab1[] = {"ls", "lsg", "lsc", "lsb", "lsa", NULL};
	int size = 0;

	tmp_str = cut_cmd(cmd, cursor);
	if (pos == 0) {
		for (int j = 0 ; split_path[j] != NULL ; j++)
			cmd_list = add_cmd_to_array(split_path[j],
			tmp_str, cmd_list);
	}
	pwd = add_dir_to_path(pwd, tmp_str);
	tmp_str = remove_cmd_dir_path(tmp_str);
	cmd_list = add_cmd_to_array(pwd, tmp_str, cmd_list);
	if (cmd_list == NULL)
		return (0);
	//print_tab_command(tab1, 200);
	print_list(cmd_list);
	destroy_list(cmd_list);
	my_putchar('\n');
	free(pwd);
	return (0);
}