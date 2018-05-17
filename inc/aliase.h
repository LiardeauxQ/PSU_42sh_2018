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

list_t *list_create();

#endif /* ALIASE_H_ */
