# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlytvyne <vlytvyne@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/27 15:37:48 by vlytvyne          #+#    #+#              #
#    Updated: 2018/12/27 15:37:48 by vlytvyne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

INCDIR = includes/

SRC = create_rooms.c get_paths.c input.c launch_ants.c linker.c main.c queue.c utils.c utils2.c 

OBJDIR = objects

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

LIB = libft/libft.a

INCDIR = includes

FLAGS = -Wall -Werror -Wextra

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
