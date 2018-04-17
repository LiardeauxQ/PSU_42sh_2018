/*
** EPITECH PROJECT, 2017
** change_directorie_cmd.h
** File description:
** change directorie cmd header
*/

#ifndef CHANGE_DIRECTORIE_CMD_H_
#define CHNAGE_DIRECTORIE_CMD_H_

int change_dir_cmd(char ***env, char **argv);
char **update_oldpwd_var(char *env[], char current_dir[]);
char **update_pwd_var(char *env[], char current_dir[]);
char *find_env_var_value(char *env[], char *env_var);

#endif /* CHANGE_DIRECTORIE_CMD_H_ */
