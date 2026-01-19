# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idridi <idridi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 17:04:10 by idridi            #+#    #+#              #
#    Updated: 2025/12/18 19:05:25 by idridi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
#                                   SETTINGS                                   #
# **************************************************************************** #

NAME        = cub3D

CC          = cc
CFLAGS := -Wall -Wextra -Werror -g -Iinclude -Ilibft -Isrc/mlx -IGNL

# Automatically detect all .c files recursively
SRCS        = $(shell find . -name "*.c" -not -path "./mlx/*")
OBJS        = $(SRCS:%.c=%.o)

# Include directories (adjust if needed)
INC_DIR     = include
INCLUDES    = -I$(INC_DIR) -Imlx

# MiniLibX (Linux)
MLX_DIR     = mlx
MLX_LIB     = $(MLX_DIR)/libmlx.a

# X11 libs
LIBS        = -Lmlx -lmlx -lXext -lX11 -lm


# **************************************************************************** #
#                                 MAKE RULES                                    #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "✔️  Compilation OK"

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	make clean -C $(MLX_DIR)
	@echo "🧹 clean terminé."

fclean: clean
	rm -f $(NAME)
	@echo "🧹 fclean terminé."

re: fclean all

.PHONY: all clean fclean re
