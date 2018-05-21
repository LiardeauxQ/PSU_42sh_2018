##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile
##

SRC	=	src/manage_env/set_env_commande.c	\
		src/manage_env/unset_env_commande.c	\
		src/manage_env/manage_environment.c	\
		src/manage_env/manage_path_var.c	\
		src/change_dir/check_access.c	\
		src/change_dir/change_dir_cmd.c	\
		src/change_dir/manage_pwd_var.c	\
		src/echo_command/manage_quote_cmd.c	\
		src/echo_command/recup_echo_argument.c	\
		src/multiple_command/manage_fd_redirection.c	\
		src/multiple_command/manage_pipe_char.c	\
		src/multiple_command/manage_multiple_command.c	\
		src/multiple_command/arrow_char_redirection.c	\
		src/multiple_command/redirection_char.c	\
		src/multiple_command/condition_command.c	\
		src/parse_cmd_string/create_cmd_struct.c	\
		src/parse_cmd_string/destroy_cmd_struct.c	\
		src/parse_cmd_string/print_cmd_struct.c	\
		src/catch_cmd_string/read_cmd_string.c	\
		src/manage_exe_commande.c	\
		src/manage_error.c	\
		src/check_commande.c	\
		src/main.c

OBJ	=	$(SRC:.c=.o)

CC	=	cc

CFLAGS	=	-g -I inc/ -Wall -Wextra

LDFLAGS	=	-L lib/my -lmy -lncurses

NAME	=	42sh

RED		=	\033[0;31m
GREEN		=	\033[0;32m
NC		=	\033[0m
GREY		=	\033[90m
BG_COLOR	=	\033[46m

all:	$(NAME)

$(NAME):	$(OBJ)
	@echo -e '${BG_COLOR}Flags: $(LDFLAGS) $(CFLAGS)${NC}'
	@echo -e '${GREEN}Create${NC}: ${GREY}./$(NAME)${NC}'
	@make --no-print-directory -C lib/my
	@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o:	%.c
	@echo -e '${GREEN} [ OK ]${NC} Building : $<'
	@$(CC) -o $@ -c $< $(LDFLAGS) $(CFLAGS)

clean:
	@make clean -C lib/my
	@rm -f $(OBJ)
	@echo -e '${RED}Clean${NC} : OK'

fclean: clean
	@make fclean -C lib/my
	@rm -f $(NAME)
	@echo -e '${RED}Fclean${NC}: ./$(NAME) removed'

re: fclean all

.PHONY: re fclean clean all
