# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/04 07:39:24 by mmubina           #+#    #+#              #
#    Updated: 2026/01/04 16:06:43 by mmubina          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = fdf
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
LIB_DIR     = lib
MLX42_DIR   = $(LIB_DIR)/MLX42
MLX42_LIB   = $(MLX42_DIR)/build/libmlx42.a

# List of source files based on your directory structure
SRCS        = src/main.c src/parser.c src/parser_utils.c src/draw.c \
              src/draw_utils.c src/transform.c src/events.c \
              src/get_next_line.c src/get_next_line_utils.c \
              src/mini_libft/ft_split.c src/mini_libft/functions.c

OBJS        = $(SRCS:.c=.o)

# Include paths for headers
HEADERS     = -I./include -I$(MLX42_DIR)/include/MLX42

# Linker flags
LDFLAGS     = -L$(MLX42_DIR)/build -lmlx42 -lglfw -lGL -lX11 -lXext -lm -pthread

.PHONY: all clean fclean re mlx42

# 1. The 'all' rule now explicitly depends on $(NAME)
all: $(NAME)

# 2. $(NAME) depends on your objects AND the MLX library
$(NAME): $(MLX42_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(NAME) has been built successfully!"

# 3. Rule to build MLX42 library
$(MLX42_LIB):
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		mkdir -p $(LIB_DIR); \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR); \
	fi
	@cmake -B $(MLX42_DIR)/build -S $(MLX42_DIR)
	@make -C $(MLX42_DIR)/build -j4

# 4. Rule to compile your .c files into .o files
# Added the @ symbol to match the clean output you wanted
%.o: %.c
	@echo "Compiling: $(notdir $<)"
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "Objects cleaned."

fclean: clean
	@rm -f $(NAME)
	@echo "Executable and objects removed."

re: fclean all
