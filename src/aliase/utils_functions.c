/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_aliase.c
*/

#include "minishell.h"

int xstrcmp(char *str_1, char *str_2)
{
	int n = 0;

	while (str_1[n] && str_2[n] && str_1[n] == str_2[n])
		n++;
	return (str_2[n] - str_1[n]);
}

char *xstrcat(char *dest, char *src)
{
	int n = 0;
	int i = my_strlen(dest);

	while (src[n])
		dest[i++] = src[n++];
	dest[i] = '\0';
	return (dest);
}

char *xstrncat(char *dest, char *src, int len)
{
	int n  = 0;
	int i = my_strlen(dest);

	while (src[n] && n < len)
		dest[i++] = src[n++];
	dest[i] = '\0';
	return (dest);
}

char *xstrstr(char *str, char *keyword)
{
	int n = 0;

	if (str[n] != '\0') {
		while (keyword[n]) {
			if (keyword[n] != str[n])
				return (xstrstr(str + 1, keyword));
			n++;
		}
		return (str);
	} else
		return (0);
}

char *xreplace(char *src, char *key, char *nkey)
{
	char *pos;
	char *pos2;
	char *ret;
	int len = 0;

	if ((ret = malloc(my_strlen(src) + my_strlen(nkey))) == NULL)
		return (NULL);
	ret[0] = '\0';
	pos = src;
	pos2 = xstrstr(pos, key);
	len = pos2 - pos;
	xstrncat(ret, pos, len);
	xstrncat(ret, nkey, my_strlen(nkey));
	pos = pos2 + my_strlen(key);
	xstrcat(ret, pos);
	return (ret);
}

int my_strncmp(char *s1, char *s2, int n)
{
	int ret;

	if (*s1 == *s2 && *s1 && *s2 && n > 1)
		return (my_strncmp(++s1, ++s2, --n));
	ret = *s1 - *s2 > 0 ? 1 : *s1 - *s2;
	ret = ret < 0 ? -1 : ret;
	return (ret);
}

int match(char *s1, char *s2)
{
	if (*s1 == 0 && *s2 == 0)
		return (1);
	else if (*s1 == *s2 && *s1 != 42)
		return (match(s1 + 1, s2 + 1) > 0 ? 1 : 0);
	else if (*s1 == 42 && *s2 == 42)
		return (match(s1 + 1, s2) > 0 ? 1 : 0);
	else if (*s2 == 42 && *s1 == 0)
		return (match(s1, s2 + 1) > 0 ? 1 : 0);
	else if (*s2 == 42 && *s2 != 0 && *s1 != 0)
		return (match(s1, s2 + 1) + match(s1 + 1, s2) > 0 ? 1 : 0);
	else
		return (0);
}

int count_dab(char **tab)
{
	int i = 0;

	while (tab[i] != NULL)
		++i;
	return (i);
}
