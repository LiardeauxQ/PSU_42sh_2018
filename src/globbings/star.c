/*
** EPITECH PROJECT, 2018
** star
** File description:
** 42sh
*/

#include "minishell.h"

char	**match_files(char *read, char *path, int ac)
{
	int		i = 0;
	int		j = 0;
	static	int	ptr = ac;

	while (path[i] != '*')
		++i;
	path = my_revstr(path);
	while (path[j] != '*')
		++j;
	path = my_revstr(path);
	if (my_strncmp(read, path, i) == 0 &&
		my_strncmp(read, path, j) == 0) {
		if (ptr == ac)
			tab[ptr] = realloc(tab[ptr], my_strlen(tab[ac]));
		else {//insérer le nouvel élément ici, et c est tout !
			tab[ptr] = realloc(tab[ptr], my_strlen(tab[ac]));
		}
	return (tab);
}

char	*get_star(char *path)
{
	char	*file = NULL;

	if ((path = my_revstr(path)) == NULL)
		return (NULL);
	file = malloc(sizeof(char) * 2);
	for (int i = 0; path[i] != '\0' ||
			(path[i] == '/' && i > 0); i++) {
		file = realloc(file, 1);
		file[i] = path[i];
	}
	return (path);
}

char	*find_path(char *str)
{
	int	ret = 0;
	int	i = 0;
	char	*path = NULL;

	for (int i; str[i] != '*'; i++)
		if (str[i] == '\0') {
			my_puterror("Wrong pathname for globbings\n");
			return (NULL);
		} else if (str[i] == '/')
			++ret;
	if (ret == 0)
		return (path);
	path = malloc(sizeof(char) * 2);
	for (int j = 0; j < i; j++) {
		path[j] = str[i];
		path = realloc(path, 1);
	}
	free(str);
	return (path);
}

int	find_star(char **tab, int ac)
{
	for (int i = 1; tab[i] != NULL; i++)
		for (int j = 0; tab[i][j] != '\0' ||
				tab[i][j] == '*'; j++)
			ac = i;
	return (ac);
}

char	**trigger_star(char **tab)
{
	DIR	*dirp = NULL;
	int	ac = -1;

	if ((ac = find_star(tab, ac)) < 0)
		return (tab);
	if ((path = find_path(tab[ac])) == NULL)
		return (NULL);
	if ((dirp = opendir(path)) == NULL)
		return (NULL);
	path = get_star(path);
	while (readdir(dirp) != NULL)
		tab = match_files(dirp->d_name, path, ac);
	closedir(dirp);
	return (tab);
}
