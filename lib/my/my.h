/*
** EPITECH PROJECT, 2017
** my.h
** File description:
** main header
*/

#ifndef MY_H_
#define MY_H_

#ifndef READ_SIZE
#	define READ_SIZE (153)
#endif /* !READ_SIZE */
#define ERROR_INVALID_ARGUMENT 84
#define ERRROR_MALLOC 84
#define ERROR_EXE 84

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
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
void destroy_2darray(char **array);
char *my_strcat(char *dest, char const *src);
char *get_next_line(int fd);
void check_malloc(void *array);
int check_same_caractere(char str, char *c);
int check_same_str(char *str1, char *str2);
char **initialize_db_array(char *str1, char *str2, int size);
int count_char_rec(char *str, char *c);

#endif /* MY_H_ */
