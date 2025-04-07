# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/19 10:29:45 by igchurru          #+#    #+#              #
#    Updated: 2025/04/03 10:50:32 by igchurru         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -g3 -O0
MLX42_FLAGS = -ldl -lglfw -pthread

SRC_DIR = sources
OBJ_DIR = objects

SRCS = $(wildcard $(SRC_DIR)/**/*.c, $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

LIBS = MLX42/build/libmlx42.a libft/libft.a

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

all: libft mlx42 $(NAME)

$(NAME): $(OBJS) $(LIBS)
	@$(CC) $(CFLAGS) $(MLX42_FLAGS) -lm $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)-> MiniRT: miniRT compilation OK$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Create the operations subdirectory
$(OBJ_DIR)/operations:
	@mkdir -p $(OBJ_DIR)/operations

$(OBJ_DIR)/parse:
	@mkdir -p $(OBJ_DIR)/parse

$(OBJ_DIR)/test:
	@mkdir -p $(OBJ_DIR)/test

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(OBJ_DIR)/operations $(OBJ_DIR)/parse $(OBJ_DIR)/test
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C ./libft
	@echo "$(YELLOW)-> MiniRT: All .o files removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@rm -rf MLX42/build
	@make fclean -C ./libft
	@echo "$(RED)-> MiniRT: miniRT removed$(RESET)"

re: fclean all

libft:
	make bonus -s -C libft

mlx42:
	@if [ ! -d "MLX42/build" ]; then \
		mkdir -p MLX42/build && cd MLX42/build && cmake ..; \
	fi
	make -s -C MLX42/build

update:
	@git submodule update --init --recursive --remote
	@echo "$(BLUE)-> MiniRT: Submodules updated to last commit$(RESET)"

.PHONY: all clean fclean re libft mlx42
