# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nobila <nobila@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/22 16:56:22 by notraore          #+#    #+#              #
#    Updated: 2017/11/25 23:23:33 by nobila           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=rtv1
CC=gcc
SRC=srcs/main.c srcs/error.c srcs/keyboard.c srcs/init.c srcs/vector_op.c \
srcs/vector_op_scal.c
OBJ=main.o error.o keyboard.o init.o vector_op.o vector_op_scal.o
FLAGS=-Wall -Wextra -Werror
LIB=-L ./libft -lft
MLX=-L ./miniLibx_macos -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
	@ echo "\033[92m\t\t\t---> ✓ libft created. ✓ <---\033[0m"
	@ make -C ./libft
	@ echo "\033[92m\t---> ✓ rtv1 program has been successfully created. ✓ <---\033[0m"
	@ $(CC) $(FLAGS) $(OBJ) -o $(NAME) $(MLX) $(LIB)
$(OBJ): $(SRC)
	@ $(CC) $(FLAGS) -c $(SRC)
clean:
	@ echo "\033[1;33m---> All .o files cleared. ✓ <---\033[0m"
	@ rm -f $(OBJ)
	@ make -C ./libft clean
fclean: clean
	@ echo "\033[1;33m---> Everything has been cleared. ✓ <---\033[2;00m"
	@ rm -f $(NAME)
	@ make -C ./libft fclean
re: fclean all

.PHONY: clean, fclean, re
