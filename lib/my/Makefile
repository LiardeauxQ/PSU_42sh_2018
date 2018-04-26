##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile
##

SRCLIB	=	my_putchar.c	\
		my_put_nbr.c	\
		my_putstr.c	\
		my_puterror.c	\
		my_strlen.c	\
		my_revstr.c	\
		my_strcpy.c	\
		my_strcmp.c	\
		my_strdup.c	\
		my_strcat.c	\
		manage_2darray.c	\
		manage_3d_array.c	\
		get_next_line.c	\
		my_str_to_wordtab/my_str_to_wordtab.c	\
		my_str_to_wordtab/my_str_to_wordtab_str.c	\
		my_str_to_wordtab/my_str_to_wordtab_no_supr.c	\
		remove_needless_char.c	\
		my_strtoi.c

OBJLIB	=	$(SRCLIB:.c=.o)

NAMELIB	=	libmy.a

CFLAGS	=	-g -W

$(NAMELIB):	$(OBJLIB)
	ar rc $(NAMELIB) $(OBJLIB)

clean:
	rm -f $(OBJLIB)

fclean: clean
	rm -f $(NAMELIB)

re: fclean all

.PHONY: re fclean clean all
