/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** aliase.h
*/

#ifndef ALIASE_H_
#define ALIASE_H_

typedef struct list_alias_s {
	char *cmd;
	char *new_cmd;
	struct list_alias_s *next;
} list_alias_t;

/*bacis alias and unalias command*/

list_alias_t *my_alias(list_alias_t *list_alias, char **cmd);
list_alias_t *my_unalias(list_alias_t *list_alias, char **cmd);

/*utility unctions*/

int count_str_size(char *str, int i);
int count_equal(char *str);
char *new_str(char *cmd, int size, char *new_cmd);
void destroy_list_alias(list_alias_t *list_alias);
int remove_last_alias(list_alias_t **list_alias);

/*manage alias chained list*/

list_alias_t *push_back_list_alias(list_alias_t *list_alias, char *cmd,
	char *new_cmd);
void print_alias(list_alias_t *list_alias);
int list_length(list_alias_t *list_alias);
list_alias_t *new_list_alias(void);
int is_empty_list(list_alias_t *list_alias);
int list_length(list_alias_t *list_alias);

/*Check alias and unalias existence*/

list_alias_t *is_unalias(list_alias_t *list_alias, char *cmd);
list_alias_t *check_unalias(list_alias_t *list_alias, list_alias_t *tmp,
	list_alias_t *previous, char *cmd);
char *replace_alias(list_alias_t *list_alias, char *cmd);

#endif /* ALIASE_H_ */
