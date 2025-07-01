# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 12:51:25 by mlitvino          #+#    #+#              #
#    Updated: 2025/07/01 17:47:44 by mlitvino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc -Ofast -Wall -Wextra -Werror

HEADERS		= -I$(LIBFT_DIR)/$(INCLD_DIR) -I$(INCLD_DIR) -I$(MLX_DIR)/include
LIBS		= -L$(MLX_DIR)/build $(MLX) -lz -ldl -lglfw -pthread -lm

NAME		= cub3D
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/build/libmlx42.a

OBJ_DIR		= obj
INCLD_DIR	= includes

LIBS_DIR	= ../lib
MLX_DIR		= $(LIBS_DIR)/MLX42
LIBFT_DIR	= $(LIBS_DIR)/libft

SRC_DIR		= src
RAY_DIR		= raycast
MOV_DIR		= movement
MAP_DIR		= map

SRC			= $(addprefix $(SRC_DIR)/, \
				main.c \
				init.c \
				clean.c \
				$(RAY_SRC) \
				$(MOV_SRC) \
				$(MAP_SRC) \
				)

RAY_SRC		= $(addprefix $(RAY_DIR)/, \
				raycast.c \
				find_wall.c \
				helper.c \
				utils.c \
				)

MAP_SRC		= $(addprefix $(MAP_DIR)/, \
				perror.c \
				error.c \
				free.c \
				colour_utils.c \
				file_utils.c \
				read_file.c \
				colour.c \
				map_borders.c \
				map_utils.c \
				map.c \
				surrounding.c \
				valid_file.c \
				)

MOV_SRC		= $(addprefix $(MOV_DIR)/, \
				rotate.c \
				movement.c \
				event_handler.c \
				)

OBJ			= $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))
INCLD		= $(INCLD_DIR)/cub3D.h

.SECONDARY: $(OBJ)

all: $(LIBFT) $(MLX) $(NAME)

$(MLX):
	cmake -S $(MLX_DIR) -B $(MLX_DIR)/build
	cmake --build $(MLX_DIR)/build -j6

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLD)
	@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	$(CC) $(HEADERS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.c $(INCLD)
	@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	$(CC) $(HEADERS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) $(LIBS) $(HEADERS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) all
	make -C $(LIBFT_DIR) bonus

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	make -C $(MLX_DIR)/build clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
