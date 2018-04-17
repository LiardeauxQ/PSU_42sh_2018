/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** set_env_commande.c
*/

#include "minishell.h"

static int check_good_caractere(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
	|| (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	else
		return (0);
}

static int check_setenv_var_value(char **argv)
{
	if (argv == NULL)
		return (-1);
	for (int i = 0 ; argv[1][i] != '\0' ; i++) {
		if (check_good_caractere(argv[1][i]) == 0)
			return (1);
	}
	return (0);
}

static int check_setenv_special_cases(char *env[], char **argv)
{
	int nb_arg = count_2d_array(argv);

	if (nb_arg == 1) {
		display_env_var(env);
		return (1);
	} else if (nb_arg > 3) {
		my_puterror("setenv: Too many arguments.\n");
		return (1);
	}
	if (argv[1][0] < 'A' || (argv[1][0] > 'Z'
	&& argv[1][0] < 'a') || argv[1][0] > 'z') {
		my_puterror("setenv: Variable name must");
		my_puterror(" begin with a letter.\n");
		return (1);
	}
	if (check_setenv_var_value(argv)) {
		my_puterror("setenv: Variable name must");
		my_puterror(" contain alphanumeric characters.\n");
		return (1);
	}
	return (0);
}

int set_environment_cmd(char ***env, char **argv, int size_cmd)
{
	int nb_var = count_2d_array(*env);
	int already_var = 0;
	char **stock = *env;

	if (env == NULL || argv == NULL)
		return (-1);
	if (check_setenv_special_cases(stock, argv)) {
		*env = stock;
		return (1);
	}
	if ((already_var = find_env(stock, argv[1])) != -1) {
		for (int i = 0 ; stock[already_var][i] != '\0' ; i++)
			stock[already_var][i] = '\0';
		stock[already_var] = create_var_env(argv, size_cmd);
	} else {
		stock[nb_var] = create_var_env(argv, size_cmd);
		stock[nb_var + 1] = NULL;
	}
	*env = stock;
	return (0);
}
