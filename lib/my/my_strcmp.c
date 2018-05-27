/*
** EPITECH PROJECT, 2017
** strcmp.c
** File description:
** compare to string
*/

#include "my.h"

int my_strcmp(char const *s1, char const *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (0);
	else if (my_strlen(s1) != my_strlen(s2))
		return (0);
	for (int i = 0 ; s1[i] != '\0' ; i++) {
		if (s1[i] != s2[i])
			return (0);
	}
	return (1);
}

int my_strncmp(char const *s1, char const *s2, int n)
{
	if (s1 == NULL || s2 == NULL)
		return (0);
	else if (my_strlen(s1) != my_strlen(s2))
		return (0);
	for (int i = 0 ; i < n && s1[i] != '\0' ; i++) {
		if (s1[i] != s2[i])
			return (0);
	}
	return (1);
}

int my_strcmp_with_ignore(char const *s1, char const *s2, char c)
{
	int j = 0;
	int i = 0;

	if (s1 == NULL || s2 == NULL)
		return (0);
	else if (my_strlen(s1) != my_strlen(s2))
		return (0);
	while (1) {
		while (i < my_strlen(s1) && s1[i] == c)
			i = i + 1;
		while (j < my_strlen(s2) && s2[j] == c)
			j = j + 1;
		if (i > my_strlen(s1) || j > my_strlen(s2))
			break;
		if (s1[i] != s2[j])
			return (0);
		j = j + 1;
		i = i + 1;
	}
	return (1);
}
