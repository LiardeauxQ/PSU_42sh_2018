/*
** EPITECH PROJECT, 2018
** trim_spaces
** File description:
** libfunc
*/

#include "manage_multiple_command.h"

char	*leading_spaces(char *str)
{
	char	*tmp;
	int	i = 0;
	int	j = 0;

	while (str[i] == ' ' || str[i] == '\t')
		i++;
	tmp = malloc(sizeof(char) * (my_strlen(str) - i + 5));
	while (str[i] != '\0') {
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	free(str);
	return (tmp);
}

char	*middle_spaces(char *str)
{
	char	*tmp = malloc(sizeof(char) * (my_strlen(str) + 5));
	int	i = 0;
	int	j = 0;

	while (str[j] != '\0') {
		if (str[j] != ' ') {
			tmp[i] = str[j];
			i++;
			j++;
		} else if (str[j] == ' ' && str[j + 1] != ' ') {
			tmp[i] = str[j];
			j++;
			i++;
		} else
			j++;
	}
	tmp[i] = '\0';
	free(str);
	return (tmp);
}

char	*trailing_spaces(char *str)
{
	char	*tmp;
	int	j = my_strlen(str) - 1;

	if (str[j] == ' ' || str[j] == '\t') {
		while (str[j] == ' ' || str[j] == '\t') {
			j--;
		}
		tmp = malloc(sizeof(char) * (j + 5));
		tmp[j + 1] = '\0';
		while (j != -1) {
			tmp[j] = str[j];
			j--;
		}
		free(str);
		return (tmp);
	}
	return (str);
}

char	*clean(char *str)
{
	char	*tmp;

	if (my_strlen(str) > 1) {
		tmp = leading_spaces(str);
		tmp = trailing_spaces(tmp);
		tmp = middle_spaces(tmp);
		return (tmp);
	} else
		return (str);
}
