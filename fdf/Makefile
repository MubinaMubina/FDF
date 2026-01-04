# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/04 07:39:24 by mmubina           #+#    #+#              #
#    Updated: 2026/01/04 11:43:27 by mmubina          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX42_DIR = MLX42

MLX42_LIB = $(MLX42_DIR)/build/libmlx42.a

SRCS = src/main.c \
	src/parser.c \
	src/parser_utils.c \
	src/draw.c \
	src/draw_utils.c \
	src/transform.c \
	src/events.c \
	src/get_next_line.c \
	src/get_next_line_utils.c \
	src/mini_libft/ft_split.c \
	src/mini_libft/functions.c

OBJS = $(SRCS:.c=.o)

HEADERS = -I./include -I$(MLX42_DIR)/include/MLX42

LDFLAGS = -L$(MLX42_DIR)/build -lmlx42 -lglfw -lGL -lX11 -lXext -lm -pthread

.PHONY: all clean fclean re mlx42

all: mlx42 $(NAME)

mlx42: $(MLX42_LIB)

$(MLX42_LIB):
	@echo "Building MLX42..."
	@cd $(MLX42_DIR) && cmake -B build && make -C build
	@echo "MLX42 built successfully"

$(NAME): $(OBJS) $(MLX42_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(HEADERS) $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

src/mini_libft/%.o: src/mini_libft/%.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

