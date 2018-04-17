/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** minishell.h
*/

#ifndef MINISHELL_H_
#define MINISHELL_H_

#include <fcntl.h>
#include "manage_environment.h"
#include "change_directorie_cmd.h"
#include "manage_error.h"
#include "manage_multiple_command.h"
#include "my.h"

/* check_commande.c */

int check_exe_signal(int wstatus);
int check_one_command(char *cmd, char **argv, char ***env);

#endif /* MINISHELL_H_ */
