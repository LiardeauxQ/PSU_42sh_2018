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
		my_int_tostr.c	\
		manage_2darray.c	\
		manage_3d_array.c	\
		get_next_line.c	\
		my_str_to_wordtab/my_str_to_wordtab.c	\
		my_str_to_wordtab/my_str_to_wordtab_str.c	\
		my_str_to_wordtab/my_str_to_wordtab_no_supr.c	\
		remove_needless_char.c	\
		base_convertion.c	\
		my_strtoi.c

OBJLIB	=	$(SRCLIB:.c=.o)

NAMELIB	=	libmy.a

CFLAGS	=	-g -W -I.

RED		=	\033[0;31m
GREEN		=	\033[0;32m
NC		=	\033[0m
GREY		=	\033[90m
BG_COLOR	=	\033[46m

$(NAMELIB):	$(OBJLIB)
	@echo -e '${BG_COLOR}Flags: $(CFLAGS)${NC}'
	@echo -e '${GREEN}Create${NC}: ${GREY}$(NAMELIB)${NC}'
	@ar rc $(NAMELIB) $(OBJLIB)

%.o:	%.c
	@echo -e '${GREEN} [ OK ]${NC} Building : $<'
	@$(CC) -o $@ -c $< $(LDFLAGS) $(CFLAGS)

clean:
	@rm -f $(OBJLIB)
	@echo -e '${RED}Clean${NC} : OK'

fclean: clean
	@rm -f $(NAMELIB)
	@echo -e '${RED}Fclean${NC} : OK'

re: fclean all

.PHONY: re fclean clean all
