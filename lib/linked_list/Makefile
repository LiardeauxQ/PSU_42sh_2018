##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile
##

SRCLIB	=	list_operation.c	\
		print_list.c	\
		count_list_size.c	\
		destroy_list.c

OBJLIB	=	$(SRCLIB:.c=.o)

NAMELIB	=	liblinklist.a

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
