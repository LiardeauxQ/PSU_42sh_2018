/*
** EPITECH PROJECT, 2017
** lib
** File description:
** my_str_to_wordtab_no_supr.c
*/

#include "../my.h"

static char *add_sep_str(char *str, char *str1, char *str2, int *j)
{
	int a = 0;

	while (a < my_strlen(str2)) {
		str[a] = str1[*j];
		a = a + 1;
		*j = *j + 1;
	}
	str[a] = '\0';
	return (str);
}

static int remove_space_and_tab(char *str, int j)
{
	while (str[j] != '\0' && (str[j] == ' ' || str[j] == '\t'))
		j = j + 1;
	return (j);
}

char **my_str_to_wordtab_no_supr(char *s1, char *s2)
{
	char **t_s = initialize_db_array(s1, s2, count_char_rec(s1, " \t") + 1);
	int j = 0;
	int k = 0;

	for (j ; s1[j] != '\0' && check_same_str(s1 + j, s2) == 1 ; j++);
	for (int a = 0 ; j < my_strlen(s1) ; a = a) {
		t_s[k][a] = s1[j];
		j = j + 1;
		a = a + 1;
		if (s1[j] == '\0' || s1[j] == ' ' || s1[j] == '\t') {
			t_s[k++][a] = '\0';
			a = 0;
			j = remove_space_and_tab(s1, j);
		} else if (check_same_str(s1 + j, s2) == 1) {
			t_s[k++][a] = '\0';
			a = 0;
			t_s[k++] = add_sep_str(t_s[k], s1, s2, &j);
		}
	}
	t_s[k] = NULL;
	return (t_s);
}
