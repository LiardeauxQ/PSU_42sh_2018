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
		src/manage_inhibitors/my_str_to_backslash_tab.c	\
		src/manage_inhibitors/my_str_to_back_tab.c	\
		src/manage_inhibitors/trim_spaces.c		\
		src/manage_inhibitors/my_is_in_str.c		\
		src/manage_inhibitors/manage_inhibitor.c		\
		src/multiple_command/manage_fd_redirection.c	\
		src/multiple_command/manage_pipe_char.c		\
		src/multiple_command/manage_multiple_command.c	\
		src/multiple_command/arrow_char_redirection.c	\
		src/multiple_command/redirection_char.c	\
		src/multiple_command/condition_command.c	\
		src/parse_cmd_string/create_cmd_struct.c	\
		src/parse_cmd_string/destroy_cmd_struct.c	\
		src/parse_cmd_string/print_cmd_struct.c	\
		src/catch_cmd_string/key_event.c	\
		src/catch_cmd_string/buffer_modification.c	\
		src/catch_cmd_string/read_cmd_string.c	\
		src/catch_cmd_string/cmd_operation.c	\
		src/catch_cmd_string/order_cmd_list.c	\
		src/catch_cmd_string/tab_completion.c	\
		src/catch_cmd_string/tab_key_management.c	\
		src/catch_cmd_string/movement_history.c	\
		src/alias/init_list_alias.c	\
		src/alias/manage_alias.c	\
		src/alias/utils_alias.c	\
		src/globbings/match_globbings.c	\
		src/globbings/split_globbing_cmd.c	\
		src/globbings/star.c	\
		src/manage_exe_commande.c	\
		src/manage_error.c	\
		src/check_commande.c	\
		src/history/manage_history.c	\
		src/history/history_counter.c	\
		src/main.c

OBJ	=	$(SRC:.c=.o)

CC	=	cc

CFLAGS	=	-g -I inc/ -I lib/linked_list -Wall -Wextra

LDFLAGS	=	-L lib/my -L lib/linked_list -llinklist -lmy -lncurses

CPPFLAGS	= -I inc/

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
	@make --no-print-directory -C lib/linked_list
	@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o:	%.c
	@echo -e '${GREEN} [ OK ]${NC} Building : $<'
	@$(CC) -o $@ -c $< $(LDFLAGS) $(CFLAGS)

clean:
	@make clean --no-print-directory -C lib/my
	@make clean --no-print-directory -C lib/linked_list
	@rm -f $(OBJ)
	@echo -e '${RED}Clean${NC} : OK'

fclean: clean
	@make fclean --no-print-directory -C lib/my
	@make fclean --no-print-directory -C lib/linked_list
	@rm -f $(NAME)
	@echo -e '${RED}Fclean${NC}: ./$(NAME) removed'

re: fclean all

.PHONY: re fclean clean all
