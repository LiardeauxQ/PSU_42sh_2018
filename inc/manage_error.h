/*
** EPITECH PROJECT, 2017
** manage_error.h
** File description:
** manage_error header
*/

#ifndef MANAGE_ERROR_H_
#define MANAGE_ERROR_H_

int manage_cmd_not_found(char *cmd_name);
int can_access_to_file(char *filename);
int check_cd_error(char *directory, int cmd_size);
int print_redirection_error(int error);;

#endif /* MANAGE_ERROR_H_ */
