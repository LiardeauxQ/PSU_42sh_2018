/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** echo_command.h
*/

#ifndef ECHO_COMMAND_H_
#define ECHO_COMMAND_H_

typedef struct echo_cmd_s {
	char *str;
	int quote;
} echo_cmd_t;

/* manage_quote_cmd.c */

echo_cmd_t *manage_quote_cmd(char *cmd);

/* recup_echo_argument.c */

int execute_echo_command(cmd_t *cmd);

#endif /* ECHO_COMMAND_H_ */
