##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile
##

SRC	=	src/manage_env/set_env_commande.c		\
		src/manage_env/unset_env_commande.c		\
		src/manage_env/manage_environment.c		\
		src/manage_env/manage_path_var.c		\
		src/manage_inhibitors/my_free_tab.c		\
		src/manage_inhibitors/my_str_to_backslash_tab.c	\
		src/manage_inhibitors/my_str_to_back_tab.c	\
		src/manage_inhibitors/trim_spaces.c		\
		src/manage_inhibitors/my_is_in_str.c		\
		src/change_dir/check_access.c			\
		src/change_dir/change_dir_cmd.c			\
		src/change_dir/manage_pwd_var.c			\
		src/multiple_command/manage_fd_redirection.c	\
		src/multiple_command/manage_pipe_char.c		\
		src/multiple_command/manage_multiple_command.c	\
		src/multiple_command/arrow_char_redirection.c	\
		src/multiple_command/redirection_char.c		\
		src/manage_inhibitors/manage_inhibitor.c		\
		src/parse_cmd_string/create_cmd_struct.c	\
		src/parse_cmd_string/destroy_cmd_struct.c	\
		src/parse_cmd_string/print_cmd_struct.c		\
		src/manage_exe_commande.c			\
		src/manage_error.c				\
		src/check_commande.c				\
		src/main.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-W -Wall -Wextra -g3

LDFLAGS	=	-L lib/my -lmy

CPPFLAGS	= -I inc/

NAME	=	42sh

all:	$(NAME)

$(NAME):	$(OBJ)
	make -C lib/my
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	make clean -C lib/my
	rm -f $(OBJ)

fclean: clean
	make fclean -C lib/my
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
