# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/29 15:05:55 by lsalmi            #+#    #+#              #
#    Updated: 2023/10/11 13:46:40 by esirnio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = ./libft/libft.a
SRCS =	add_envs.c builtins.c cd.c children.c delete_envs.c echo.c \
		env_helpers.c errors.c more_error.c executer.c expansion.c \
		expansion_utils.c here_doc.c lexer.c lexer_helpers.c \
		main.c make_command.c parser.c path.c \
		print_envs.c pwd.c redir.c signal.c split_input.c split_utils.c utils.c
OBJS = $(SRCS:.c=.o)

INCL = -I /minishell.h

O_FLAGS = -lreadline -L/opt/homebrew/opt/readline/lib

C_FLAGS = -I/opt/homebrew/opt/readline/include

FLAGS = -Wall -Wextra -Werror

all: $(NAME) $(OBJS)

$(NAME): $(OBJS) $(LIBFT)
	@cc $(^) -o $(@) $(C_FLAGS) $(O_FLAGS)
	@echo "Executable $(@) created"
$(LIBFT):
	@make -s -C $(@D)

%.o: %.c
	@cc -c $(FLAGS) $(C_FLAGS) $(INCL) $(<) -o $(@)

clean:
	@rm -f $(OBJS)
	@make -s -C libft clean
	@echo "Object files deleted"

fclean: clean
	@make -s -C libft fclean
	@rm -f $(NAME)
	@echo "$(NAME) deleted"

re: fclean all

.PHONY: all clean fclean re
