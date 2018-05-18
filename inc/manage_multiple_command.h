/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** manage_multiple_command.h
*/

#ifndef MANAGE_MULTIPLE_COMMAND_H_
#define MANAGE_MULTIPLE_COMMAND_H_

#define INPUT_REDIR_ERROR -2
#define OUTPUT_REDIR_ERROR -3

typedef struct fildes_pipe_s {
	int *fildes;
	int *action_rw;
	int size;
} fildes_pipe_t;

typedef int (**redir)(char ***, cmd_t *, char *, fildes_pipe_t *);

/* manage_exe_commande.c */

int exe_cmd(char *split_path, char **arg, char *env[], int *alrd_path);
char *add_cmd_to_path(char *cmd_name, char *split_path, int *alrd_path);
int check_already_path(char *pathname);

/* manage_multiple_command.c */

int check_one_separator_command(cmd_t *cmd, char ***env);
int analyse_cmd_struct(cmd_t *cmd, char ***env);
int check_if_redir_error(cmd_t *cmd);
int manage_multiple_commande(char *str_cmd, char ***env);

/* manage_fd_redirection.c */

void change_fds_priority(fildes_pipe_t *fd_pr, int cmd_pos);
void choose_dup_fd(fildes_pipe_t *fd_pr);
void close_files(fildes_pipe_t *fd_pr);
fildes_pipe_t initialize_tmp_fildes_descriptor(cmd_t *cmd);
void destroy_fildes_pipe(fildes_pipe_t *fd_pr);

/* manage_pipe_char */

int manage_pipe(cmd_t *cmd, char ***env);

/* arrow_char_redirection.c */

int double_right_arrow(char ***env, cmd_t *cmd, char *filename,
	fildes_pipe_t *fd_pr);
int double_left_arrow(char ***env, cmd_t *cmd, char *end_str,
	fildes_pipe_t *fd_pr);
int simple_right_arrow(char ***env, cmd_t *cmd, char *filename,
	fildes_pipe_t *fd_pr);
int simple_left_arrow(char ***env, cmd_t *cmd, char *filename,
	fildes_pipe_t *fd_pr);

/* redirection_char.c */

char **remove_redir_char(char **argv);
int check_if_redirection(char **split_cmd);
int check_redirections_char(cmd_t *cmd, int pos);
int manage_redirection(cmd_t *cmd, char ***env, int type, fildes_pipe_t *fd_pr);

/* condition_command.c */

int or_condition_cmd(cmd_t *cmd, char ***env);
int and_condition_cmd(cmd_t *cmd, char ***env);

#endif /* MANAGE_MULTIPLE_COMMAND_H_ */
