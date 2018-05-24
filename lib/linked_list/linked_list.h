/*
** EPITECH PROJECT, 2017
** linked_list
** File description:
** linked_list.h
*/

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct list_s {
	char *data;
	struct list_s *next;
} list_t;

int append(list_t *list, char *value);
int push(list_t **list, char *value);
int print_list(list_t *list);
int pop(list_t **list);
int remove_last(list_t **list);
void destroy_list(list_t *list);
void swap(list_t **elem1, list_t **elem2);

#endif /* LINKED_LIST_H_ */