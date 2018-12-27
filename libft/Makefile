# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vadym <vadym@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/09 21:39:43 by vadym          #+#    #+#              #
#    Updated: 2018/12/09 21:39:43 by vadym         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCDIR = includes/

SRC = ft_strjoin.c ft_isdigit.c strrev.c precision_manager.c ft_memdel.c ft_putnbr.c ft_strnstr.c ft_strcmp.c ft_putstr_fd.c ft_strmap.c zero_manager.c ft_lstdel.c ft_strlcat.c ft_strlen.c ft_strrchr.c ft_toupper.c ft_strncmp.c ft_putstr.c ft_lstiter.c ft_strmapi.c ft_putchar_fd.c uitoa_base.c ft_lstmap.c get_abs.c ft_memcmp.c ft_strncat.c ft_strnequ.c ftoa.c ft_strncpy.c power.c width_manager.c ft_striter.c ft_memcpy.c reverse_list.c itoa_base.c ft_lstnew.c hash_manager.c ft_strtrim.c print_list.c zero_vars.c sort_list.c ft_lstdelone.c ft_memchr.c ft_printf.c ft_memset.c ft_putchar.c is_whitespace.c ultimate_join.c ft_strdel.c ft_bzero.c ft_isalnum.c ft_strcat.c ft_isalpha.c btoa.c ft_strequ.c ft_strclr.c lst_add_end.c ft_itoa.c ft_strchr.c parser.c ft_strnew.c ft_memalloc.c get_next_line.c ft_strsplit.c ft_putendl.c ft_memmove.c plus_space_manager.c ft_isascii.c ft_tolower.c sort_list_ascii.c ft_strcpy.c ft_strdup.c ft_lstadd.c ft_striteri.c capitalize.c get_num_str.c ft_strsub.c ft_atoi.c ft_putnbr_fd.c ft_putendl_fd.c ft_isprint.c ft_memccpy.c utils.c ft_strstr.c error_exit.c

OBJDIR = objects

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

INCDIR = includes

FLAGS = -Wall -Werror -Wextra

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

$(OBJDIR)/%.o: ./%.c $(INCDIR)/*.h | $(OBJDIR)
	gcc $(FLAGS) -o $@ -c $< -I $(INCDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -Rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
