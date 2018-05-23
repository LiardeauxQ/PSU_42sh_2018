/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** tab_completion.c
*/

#include "minishell.h"

char **open_dir_for_comparaison(char const *dirname, char const *str)
{
	DIR *dir = opendir(dirname);
	struct dirent *dirent = 0x0;
	char **same_str = 0x0;
	int size = 1;

	if (dir == 0x0)
		return (0x0);
	while ((dirent = readdir(dir)) != 0x0) {
		if (strncmp(str, dirent->d_name, my_strlen(str)) == 0
		|| my_strlen(str) == 0) {
			same_str = realloc(same_str, (size + 1)
			* sizeof(char *));
			same_str[size - 1] = strdup(dirent->d_name);
			size = size + 1;
		}
	}
	if (size > 1)
		same_str[size - 1] = 0x0;
	closedir(dir);
	return (same_str);
}

int check_cmd_already_in(char **array, char const *cmd)
{
	int already_in = 0;

	if (array == 0x0)
		return (already_in);
	for (int i = 0 ; array[i] != 0x0 ; i++) {
		if (strcmp(array[i], cmd) == 0)
			already_in += 1;
	}
	return (already_in);
}

char **add_cmd_to_array(char const *dirname, char const *cmd, char **array)
{
	static int size = 1;
	char **same_str = 0x0;

	same_str = open_dir_for_comparaison(dirname, cmd);
	if (same_str == 0x0)
		return (array);
	for (int i = 0 ; same_str[i] != 0x0 ; i++) {
		if (check_cmd_already_in(array, same_str[i]) == 0) {
			array = realloc(array, (size + 1) * sizeof(char *));
			array[size - 1] = strdup(same_str[i]);
			array[size] = 0x0;
			size = size + 1;
		}
	}
	destroy_2darray(same_str);
	return (array);
}

char *cut_cmd(char *cmd, int cursor)
{
	char *str_cut = malloc((cursor + 1) * sizeof(char));
	int i = 0;
	int j = 0;

	if (my_strlen(cmd) >= 2 && cmd[0] == '.' && cmd[1] == '/')
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
	int delta = 0;

	for (int i = 0 ; cmd[i] != '\0' && cmd[i] != '/' ; i++)
		delta += 1;
	if (delta != my_strlen(cmd))
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
	j = my_strlen(new_pwd);
	size += my_strlen(cmd) + 1;
	new_pwd = realloc(new_pwd, size + 1);
	for (int i = 0 ; cmd[i] != '\0' && cmd[i] != '/' ; i++) {
		new_pwd[j] = cmd[i];
		j = j + 1;
	}
	new_pwd[j] = '\0';
	return (new_pwd);
}

int find_cmd_completion(char *cmd, int cursor, int pos)
{
	char *tmp_str = NULL;
	char *path = getenv("PATH");
	char *pwd = getenv("PWD");
	char **split_path = my_str_to_wordtab(path, ":");
	char **stock_same_cmd = NULL;
	int i = 0;

	tmp_str = cut_cmd(cmd, cursor);
	if (pos == 0) {
		for (int j = 0 ; split_path[j] != NULL ; j++)
			stock_same_cmd = add_cmd_to_array(split_path[j], tmp_str,
			stock_same_cmd);
	}
	pwd = add_dir_to_path(pwd, tmp_str);
	tmp_str = remove_cmd_dir_path(tmp_str);
	stock_same_cmd = add_cmd_to_array(pwd, tmp_str, stock_same_cmd);
	if (stock_same_cmd == NULL)
		return (0);
	for (int j = 0 ; stock_same_cmd[j] != NULL ; j++) {
		printf("%s\n", stock_same_cmd[j]);
	}
	free(pwd);
	return (0);
}