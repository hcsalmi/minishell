# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 16:33:11 by esirnio           #+#    #+#              #
#    Updated: 2023/08/15 19:37:41 by esirnio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_array_size.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c\
		ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c\
		ft_memset.c ft_strcat.c ft_strchr.c ft_strcmp.c ft_strcpy.c ft_strdup.c\
		ft_strlcat.c ft_strlen.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strrchr.c\
		ft_strstr.c ft_strnstr.c ft_toupper.c ft_tolower.c ft_putchar.c ft_putnbr.c\
		ft_putendl.c ft_putendl_error.c ft_putchar_fd.c ft_itoa.c ft_putstr.c ft_strequ.c ft_strnequ.c\
		ft_strjoin.c ft_isspace.c ft_str_error.c ft_strtrim.c ft_strsplit.c ft_memalloc.c\
		ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c\
		ft_strmap.c ft_strmapi.c ft_strsub.c ft_putstr_fd.c ft_putnbr_fd.c\
		ft_putendl_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c\
		ft_lstmap.c ft_intlen.c ft_free_array.c get_next_line.c ft_itoa_base.c
PRINTF_PATH = ft_printf
PRINTF = $(PRINTF_PATH)/c_conversion.c $(PRINTF_PATH)/float.c $(PRINTF_PATH)/ft_printf.c $(PRINTF_PATH)/helper_functions.c\
	$(PRINTF_PATH)/hexa.c $(PRINTF_PATH)/integer.c $(PRINTF_PATH)/pou_conversions.c $(PRINTF_PATH)/print_float.c\
	$(PRINTF_PATH)/print_integer.c $(PRINTF_PATH)/print.c $(PRINTF_PATH)/set.c $(PRINTF_PATH)/specifier.c $(PRINTF_PATH)/width_precision.c
PRINT_O_FILES = c_conversion.o float.o ft_printf.o helper_functions.o hexa.o integer.o pou_conversions.o print_float.o\
	print_integer.o print.o set.o specifier.o width_precision.o
OBJ = $(SRCS:%.c=%.o) $(PRINT_O_FILES) 
COMP = cc -c
FLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes/

all: $(NAME)

$(NAME):
	$(COMP) $(FLAGS) $(INCLUDES) $(SRCS) $(PRINTF)
	ar rcs $(NAME) $(OBJ)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
