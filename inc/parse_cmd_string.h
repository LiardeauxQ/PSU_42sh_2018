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
	int exit_status;
	char *cmd;
	char **argv;
	struct cmd_s *childs;
	struct cmd_s *parent;
} cmd_t;

/* create_cmd_struct.c */

int find_separator(char *str_cmd, struct cmd_s *cmd);
cmd_t *create_cmd_struct(char *str_cmd);

/* display_cmd_struct.c */

void display_cmd(cmd_t *cmd);

/* destroy_cmd_struct.c */

void destroy_cmd(cmd_t *cmd);

/* split_globbing_cmd.c */

int find_path_pos(char *str);
char *get_star(char *str);
char *find_path(char *str);

/* match_globbings.c */

int match(char *str, char *s);

#endif /* PARSE_CMD_STRING_H_ */
