/*
** EPITECH PROJECT, 2017
** manage_environment.h
** File description:
** manage_environment header
*/

#ifndef MANAGE_ENVIRONMENT_H_
#define MANAGE_ENVIRONMENT_H_

int find_env(char *env[], char const *var_to_search);
void display_env_var(char *env[]);

/* set_env_commande.c */

int set_environment_cmd(char ***env, char **argv, int size_cmd);
char **split_commande_string(char *cmd);
char *create_var_env(char **argv, int size_cmd);

/* unset_env_commande.c */

int unset_env_commande(char ***env, char **argv);

char *update_var_env(char *var_name, char *var_value);
char **split_path_var(char *path_v, char *c);
int check_if_is_cmd(char *env[], char *cmd_name);
int manage_executable(char *env[], char **arg);
char *split_cmd_when_space(char *arg, char *cmd, int *b);
char *manage_quoting_marks(char *arg, char *cmd, int *b);
char *add_cmd_to_path(char *cmd_name, char *split_path, int *alrd_path);
int count_2Darray_size(char *array[]);
int count_words(char str[]);

#endif /* MANAGE_ENVIRONMENT_H_ */
