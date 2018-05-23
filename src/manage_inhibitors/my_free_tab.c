/*
** EPITECH PROJECT, 2018
** my_free_tab
** File description:
** lib func
*/

#include "manage_multiple_command.h"

void	my_free_tab(char **tab)
{
	for (int i = 0; tab[i] != NULL; i++)
		free(tab[i]);
	free(tab);
}
