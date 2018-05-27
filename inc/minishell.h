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
#include "my.h"
#include <time.h>
#include "parse_cmd_string.h"
#include "aliase.h"

typedef struct shell_s {
	char **env;
	cmd_t *cmd;
	list_alias_t *alias;
} shell_t;

#include "manage_environment.h"
#include "change_directorie_cmd.h"
#include "manage_error.h"
#include "manage_multiple_command.h"
#include "echo_command.h"
#include "catch_cmd_string.h"

/* check_commande.c */

int check_exe_signal(int wstatus);
int check_one_command(cmd_t *cmd, shell_t *shell);

/* manage_history.c */

void stock_history(int fd, char *buf);
int manage_history_command(char **argv);
void display_history_count(int number);

#endif /* MINISHELL_H_ */
