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
#include <curses.h>
#include <term.h>
#include <dirent.h>
#include <time.h>
#include "manage_environment.h"
#include "change_directorie_cmd.h"
#include "manage_error.h"
#include "parse_cmd_string.h"
#include "manage_multiple_command.h"
#include "echo_command.h"
#include "catch_cmd_string.h"
#include "my.h"

/* check_commande.c */

int check_exe_signal(int wstatus);
int check_one_command(cmd_t *cmd, char ***env);

/* manage_history.c */

void stock_history(int fd, char *buf);
int manage_history_command(char ***env, char **argv);
void display_history_count(int number);

#endif /* MINISHELL_H_ */
