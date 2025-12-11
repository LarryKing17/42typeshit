# **************************************************************************** #
#                                   COLORS                                     #
# **************************************************************************** #

RESET   = \033[0m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m

# **************************************************************************** #
#                                   PROJECT                                    #
# **************************************************************************** #

NAME    = cub3d

# **************************************************************************** #
#                                   DIRECTORIES                                #
# **************************************************************************** #

SRC_DIR = src
PARSE_DIR = $(SRC_DIR)/parsing
RAY_DIR = $(SRC_DIR)/raycasting
UTILS_DIR = $(SRC_DIR)/utils
GNL_DIR = GNL
INC_DIR = includes

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = src/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

# **************************************************************************** #
#                                   FILES                                       #
# **************************************************************************** #

SRCS = $(PARSE_DIR)/parse_file.c \
       $(PARSE_DIR)/parse_line.c \
       $(PARSE_DIR)/parse_texture.c \
       $(PARSE_DIR)/parse_color.c \
       $(PARSE_DIR)/parse_map.c \
       $(PARSE_DIR)/validate_map.c \
       $(RAY_DIR)/raycasting.c \
       $(UTILS_DIR)/ft_free_tab.c \
       $(UTILS_DIR)/utils.c \
       $(SRC_DIR)/main.c \
       $(GNL_DIR)/get_next_line.c \
       $(GNL_DIR)/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

# **************************************************************************** #
#                                   COMPILATION                                #
# **************************************************************************** #

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I$(INC_DIR) -I$(GNL_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	@echo "$(BLUE)[Libft] Compilation...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@echo "$(BLUE)[Minilibx] Compilation...$(RESET)"
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	@echo "$(BLUE)[Cub3D] Compilation...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -lX11 -lXext -lm -o $(NAME)
	@echo "$(GREEN)[OK] cub3d ready !$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)[Clean] Removing .o...$(RESET)"
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@echo "$(YELLOW)[Fclean] Removing executable...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
