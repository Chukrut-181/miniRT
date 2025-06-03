# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/19 10:29:45 by igchurru          #+#    #+#              #
#    Updated: 2025/06/03 10:39:27 by igchurru         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
BONUS_NAME = miniRT_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -g3 -O0
MLX42_FLAGS = -ldl -lglfw -pthread

OBJ_DIR = objects
BONUS_OBJ_DIR = objects_bonus

SRCS = sources/color_operations.c \
		sources/create_ambient.c \
		sources/create_camera.c \
		sources/create_cylinder.c \
		sources/create_light.c \
		sources/create_plane.c \
		sources/create_sphere.c \
		sources/error.c \
		sources/execute.c \
		sources/hooks.c \
		sources/intersections_utils.c \
		sources/intersections.c \
		sources/light_shading_utils.c \
		sources/light_shading.c \
		sources/main.c \
		sources/matrix_determinant.c \
		sources/matrix_operations.c \
		sources/matrix_transformation.c \
		sources/parse.c \
		sources/ray.c \
		sources/rotation.c \
		sources/tuple_creation.c \
		sources/tuple_operations.c \
		sources/vector_operations.c \
		sources/world.c \

OBJS = $(patsubst $(SRCS)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

BONUS_SRCS = sources_bonus/color_operations_bonus.c \
		sources_bonus/create_ambient_bonus.c \
		sources_bonus/create_camera_bonus.c \
		sources_bonus/create_cylinder_bonus.c \
		sources_bonus/create_light_bonus.c \
		sources_bonus/create_plane_bonus.c \
		sources_bonus/create_cube_bonus.c \
		sources_bonus/create_sphere_bonus.c \
		sources_bonus/error_bonus.c \
		sources_bonus/execute_bonus.c \
		sources_bonus/hooks_bonus.c \
		sources_bonus/intersect_cube_bonus.c \
		sources_bonus/intersections_utils_bonus.c \
		sources_bonus/intersections_bonus.c \
		sources_bonus/light_shading_utils_bonus.c \
		sources_bonus/light_shading_bonus.c \
		sources_bonus/main_bonus.c \
		sources_bonus/matrix_determinant_bonus.c \
		sources_bonus/matrix_operations_bonus.c \
		sources_bonus/matrix_transformation_bonus.c \
		sources_bonus/parse_bonus.c \
		sources_bonus/ray_bonus.c \
		sources_bonus/rotation_bonus.c \
		sources_bonus/tuple_creation_bonus.c \
		sources_bonus/tuple_operations_bonus.c \
		sources_bonus/vector_operations_bonus.c \
		sources_bonus/world_bonus.c \

BONUS_OBJS = $(patsubst $(BONUS_SRCS)/%.c, $(BONUS_OBJ_DIR)/%.o, $(BONUS_SRCS))

LIBS = lib/minilibx/libmlx.a lib/libft/libft_bonus.a

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

all: libft mlx42 $(NAME)

bonus: libft mlx42 $(BONUS_NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(MLX42_FLAGS) -lm $(OBJS) $(LIBS) -lX11 -lXext -o $(NAME)
	@echo "$(GREEN)-> MiniRT: miniRT compilation OK$(RESET)"

$(BONUS_NAME): $(BONUS_OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(MLX42_FLAGS) -lm $(BONUS_OBJS) $(LIBS) -lX11 -lXext -o $(BONUS_NAME)
	@echo "$(GREEN)-> MiniRT Bonus: miniRT_bonus compilation OK$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BONUS_OBJ_DIR):
	@mkdir -p $(BONUS_OBJ_DIR)

$(OBJ_DIR)/operations:
	@mkdir -p $(OBJ_DIR)/operations

$(BONUS_OBJ_DIR)/operations:
	@mkdir -p $(BONUS_OBJ_DIR)/operations

$(OBJ_DIR)/parse:
	@mkdir -p $(OBJ_DIR)/parse

$(BONUS_OBJ_DIR)/parse:
	@mkdir -p $(BONUS_OBJ_DIR)/parse

$(OBJ_DIR)/test:
	@mkdir -p $(OBJ_DIR)/test

$(BONUS_OBJ_DIR)/test:
	@mkdir -p $(BONUS_OBJ_DIR)/test

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(OBJ_DIR)/operations $(OBJ_DIR)/parse $(OBJ_DIR)/test
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c | $(BONUS_OBJ_DIR) $(BONUS_OBJ_DIR)/operations $(BONUS_OBJ_DIR)/parse $(BONUS_OBJ_DIR)/test
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@make clean -C ./lib/libft
	@echo "$(YELLOW)-> MiniRT: All .o files removed$(RESET)"

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@rm -rf MLX42/build
	@make fclean -C ./lib/libft
	@echo "$(RED)-> MiniRT: miniRT and miniRT_bonus removed$(RESET)"

re: fclean all

rebonus: fclean bonus

libft:
	make bonus -s -C lib/libft

mlx42:
	make -C lib/minilibx

.PHONY: all bonus clean fclean re rebonus libft mlx42
