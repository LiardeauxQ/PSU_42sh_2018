/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** parse_cmd_string.h
*/

#ifndef PARSE_CMD_STRING_H_
#define PARSE_CMD_STRING_H_

#define SEMICOL_SEP 1
#define PIPE_SEP 2
#define OR_SEP 3
#define AND_SEP 4

typedef struct cmd_s {
	int separator;
	int redirection;
	char *cmd;
	char **argv;
	struct cmd_s *childs;
	struct cmd_s *parent;
} cmd_t;

/* create_cmd_struct.c */

int find_separator(char *str_cmd, struct cmd_s *cmd);
cmd_t *create_cmd_struct(char *str_cmd);

/* destroy_cmd_struct.c */

void display_cmd(cmd_t *cmd);

/* print_cmd_struct.c */

void destroy_cmd(cmd_t *cmd);

#endif /* PARSE_CMD_STRING_H_ */
