# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/17 16:13:57 by dguy-caz          #+#    #+#              #
#    Updated: 2017/06/17 19:49:33 by dguy-caz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	rtv1

SRCS		= 	srcs/main.c \
				srcs/ray_tracer.c \
				srcs/get_color.c \
				srcs/user_interactions.c \
				srcs/intersections.c \
				srcs/light_blocked.c \
				srcs/parsing.c \
				srcs/camera.c \
				srcs/matrix_rotation_1.c \
				srcs/matrix_rotation_2.c \
				srcs/matrix_translation.c \
				srcs/pixelisation.c \
				srcs/anti_aliasing.c \
				srcs/register_obj.c \
				srcs/vectors_op_1.c \
				srcs/vectors_op_2.c \
				srcs/vectors_op_3.c \
				srcs/colors_op_1.c \
				srcs/colors_op_2.c \
				srcs/archive_objects.c \
				srcs/create_objects.c \
				srcs/errors.c \

OBJS		= 	$(patsubst srcs/%.c,objs/%.o,$(SRCS))

CC			= 	gcc
CFLAGS		= 	-Wall -Wextra -Werror
INC			= 	-I./includes/

LIBFT		= 	./libft/libft.a
LIBFTINC	= 	-I./libft/includes/
LIBFTLINK	= 	-L./libft -lft

MLX			= 	./minilibx_macos/libmlx.a
MLXINC		= 	-I./minilibx_macos/
MLXLNK	= -L./minilibx_macos -framework OpenGL -framework AppKit -Iminilibx_macos

.SILENT:

all:		$(NAME)

$(NAME): 	$(OBJS)
			make -C ./libft
			make -C ./minilibx_macos
			$(CC) $(CFLAGS) $(INC) $(LIBFT) $(LIBFTLINK) $(MLXLNK) $(MLX) -o $@ $^
			echo "\033[92m\n---> RTv1 program created ✓\n\033[0m"

objs/%.o: 	srcs/%.c
			mkdir -p objs
		 	$(CC) $(CFLAGS) $(INC) $(LIBFTINC) $(MLXINC) -c $< -o $@

clean:		
			/bin/rm -rf objs/
			make -C libft/ clean
			make -C minilibx_macos/ clean
			echo "\033[1;33m\n---> All .o files cleared\033[0m \033[92m✓\n\033[0m"

fclean:		clean
			/bin/rm -f $(NAME)
			make -C libft/ fclean
			echo "\033[1;33m---> Everything cleared\033[2;00m \033[92m✓\n\033[0m"

re : fclean all

.PHONY: all, clean, fclean, re
