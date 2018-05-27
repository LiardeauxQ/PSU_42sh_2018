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
	char *str_tmp = 0x0;
	list_t *list = 0x0;

	if (dir == 0x0)
		return (0x0);
	while ((dirent = readdir(dir)) != 0x0) {
		if (strncmp(str, dirent->d_name, my_strlen(str)) == 0
		|| my_strlen(str) == 0) {
			if (dirent->d_type == DT_DIR) {
				str_tmp = malloc(my_strlen(dirent->d_name) + 2);
				str_tmp = strcpy(str_tmp, dirent->d_name);
				str_tmp = strcat(str_tmp, "/");
				push(&list, str_tmp);
				free(str_tmp);
			} else
				push(&list, dirent->d_name);
		}
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

char *add_dir_to_path(char *cmd)
{
	char *new_pwd = NULL;
	int size = my_strlen(cmd);
	int path_pos = 0;
	int space_pos = 0;
	int j = 0;

	if (!cinstr(cmd, '/'))
		return (strdup("./"));
	for (int i = size ; i >= 0 && cmd[i] != '/' ; i--)
		path_pos = i;
	for (int k = size ; k >= 0 && cmd[k] != ' ' && cmd[k] != '\t' ; k--)
		space_pos = k;
	if (space_pos > path_pos)
		return (strdup("./"));
	new_pwd = malloc((size + 1) * sizeof(char));
	for (int a = space_pos ; cmd[a] != '\0' && a < path_pos ; a++) {
		new_pwd[j] = cmd[a];
		j = j + 1;
	}
	new_pwd[j] = '\0';
	return (new_pwd);
}

void print_tab_command(list_t *list, int term_size)
{
	int size = 0;
	int tmp_size = 0;
	int nb_cmd = 0;
	int cmd = -1;

	for (list_t *tmp = list ; tmp != NULL ; tmp = tmp->next) {
		tmp_size = strlen(tmp->data);
		if (tmp_size > size)
			size = tmp_size;
	}
	nb_cmd = (int)(term_size / size);
	for (list_t *tmp = list ; tmp != NULL ; tmp = tmp->next) {
		cmd++;
		if (cmd == nb_cmd) {
			my_putchar('\n');
			cmd = 0;
		}
		my_putstr(tmp->data);
		for (int k = 0 ; k < (int)(size - strlen(tmp->data) + 1) ; k++)
			my_putchar(' ');
	}
}

list_t *find_cmd_completion(char *cmd, int cursor, int pos)
{
	char *tmp_str = 0x0;
	char *path = getenv("PATH");
	char **split_path = my_str_to_wordtab(path, ":");
	char *dir = NULL;
	list_t *cmd_list = 0x0;

	tmp_str = cut_cmd(cmd, cursor);
	if (pos == 0 && my_strcmp(cmd, "./") == 0) {
		for (int j = 0 ; split_path[j] != 0x0 ; j++)
			cmd_list = add_cmd_to_list(split_path[j],
			tmp_str, cmd_list);
	}
	dir = add_dir_to_path(tmp_str);
	tmp_str = remove_cmd_dir_path(tmp_str);
	if ((cmd_list = add_cmd_to_list(dir, tmp_str, cmd_list)) == 0x0)
		return (cmd_list);
	free(dir);
	return (cmd_list);
}
