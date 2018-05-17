/*
** EPITECH PROJECT, 2017
** my.h
** File description:
** main header
*/

#ifndef MY_H_
#define MY_H_

#define ERROR_INVALID_ARGUMENT 84
#define ERRROR_MALLOC 84
#define ERROR_EXE 84

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

int my_put_nbr(int nb);
void my_putchar(char c);
int my_putstr(char const *str);
int my_strlen(char const *str);
char *my_revstr(char *str);
char *my_strcpy(char *dest, const char *src);
int my_strtoi(char *number);
int my_strcmp(char const *s1, char const *s2);
char *my_strdup(char const *src);
int my_puterror(char const *str);
char ***create_3d_array(int size1, int size2);
int count_3d_array(char ***array);
void destroy_2darray(char **array);
void destroy_3darray(char ***array);
char *my_strcat(char *dest, char const *src);
char *get_next_line(int fd);
int count_char_rec(char *str, char *c);
char **my_str_to_wordtab(char *str, char *c);
int count_2d_array(char **array);
void destroy_2darray(char **array);
int count_words(char str[]);
void check_malloc(void *array);
char *remove_useless_char(char *str, char *c);
int check_if_str_in_str(char *str1, char *str2);
char **my_str_to_wordtab_str(char *str1, char *str2);
char **my_str_to_wordtab_no_supr(char *str1, char *str2);
int count_str_rec(char *str1, char *str2);

#endif /* MY_H_ */
