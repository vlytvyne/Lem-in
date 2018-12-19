# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlytvyne <vlytvyne@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/17 19:00:47 by vlytvyne          #+#    #+#              #
#    Updated: 2018/12/17 19:00:47 by vlytvyne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

INCDIR = includes/

SRC = main.c 

OBJDIR = objects

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

LIB = libft/libft.a

INCDIR = includes

FLAGS = 

.PHONY: all clean fclean re cleanlib fcleanlib relib

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	gcc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

$(LIB):
	make -C libft all
	
$(OBJDIR)/%.o: ./%.c $(INCDIR)/*.h | $(OBJDIR)
	gcc $(FLAGS) -o $@ -c $< -I $(INCDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -Rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

cleanlib:
	make -C libft clean

fcleanlib:
	make -C libft fclean

relib:
	make -C libft re
