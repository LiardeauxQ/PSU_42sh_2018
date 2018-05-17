/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** minishell.h
*/

#ifndef MINISHELL_H_
#define MINISHELL_H_

#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <string.h>
#include "manage_environment.h"
#include "change_directorie_cmd.h"
#include "manage_error.h"
#include "parse_cmd_string.h"
#include "manage_multiple_command.h"
#include "echo_command.h"
#include "my.h"

/* check_commande.c */

int check_exe_signal(int wstatus);
int check_one_command(cmd_t *cmd, char ***env);

#endif /* MINISHELL_H_ */
