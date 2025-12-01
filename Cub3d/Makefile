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
GNL_DIR = gnl
INC_DIR = includes

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# **************************************************************************** #
#                                   FILES                                       #
# **************************************************************************** #

SRCS = $(PARSE_DIR)/parse_texture.c \
       $(PARSE_DIR)/parse_color.c \
       $(PARSE_DIR)/parse_map.c \
       $(RAY_DIR)/raycasting.c \
       $(SRC_DIR)/main.c \
       $(GNL_DIR)/get_next_line.c \
       $(GNL_DIR)/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

# **************************************************************************** #
#                                   COMPILATION                                #
# **************************************************************************** #

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I$(INC_DIR) -I$(GNL_DIR) -I$(LIBFT_DIR)/includes

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(BLUE)[Libft] Compilation...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@echo "$(BLUE)[Cub3D] Compilation...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "$(GREEN)[OK] cub3d ready !$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)[Clean] Removing .o...$(RESET)"
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(YELLOW)[Fclean] Removing executable...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
