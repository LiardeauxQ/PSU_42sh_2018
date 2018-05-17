/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** aliase.h
*/

#ifndef ALIASE_H_
#define ALIASE_H_

typedef struct list_s
{
	char *key;
	char *content;
	struct list_s *next;
	struct list_s *prev;
} list_t;

typedef struct mysh_s
{
	list_t *env_list;
	list_t *history;
	list_t *alias;
} mysh_t;

int count_dab(char **tab);
int match(char *s1, char *s2);
int my_strncmp(char *s1, char *s2, int n);
char *xreplace(char *src, char *key, char *nkey);
char *xstrstr(char *str, char *keyword);
char *xstrncat(char *dest, char *src, int len);
char *xstrcat(char *dest, char *src);
int xstrcmp(char *str_1, char *str_2);
char *tab_to_str(char **tab);
char *words_get(char *str, int word, char *seps);
int words_lenght(char *str, int word, char *seps);
int words_count(char *str, char *seps);
int is_str(char c, char *seps);
list_t *get_node_by_key(list_t *list, char *key);
int list_count(list_t *list);
int my_unalias(mysh_t *sh, char **cmd);
int my_alias(mysh_t *sh, char **cmd);
char *alias_replace(list_t *alias, char *cmd);
void alias_initialize(list_t *alias);
char *alias_get(list_t *alias, char *key);
void alias_openfile(list_t *alias, char *file);
void alias_getcontent(list_t *alias, char *str);
list_t *list_create();
list_t *list_add(list_t *list, char *key, char *content);
void list_delete_node(list_t *node);

#endif /* ALIASE_H_ */
