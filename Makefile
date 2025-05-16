# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 12:51:25 by mlitvino          #+#    #+#              #
#    Updated: 2025/05/16 16:33:39 by mlitvino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
# -Wall -Wextra -Werror
HEADERS		= -I$(LIBFT_DIR)/$(INCLD_DIR) -I$(INCLD_DIR) -I$(MLX_DIR)/include
LIBS		= -L$(MLX_DIR)/build $(MLX) -lz -ldl -lglfw -pthread -lm -o

NAME		= cub3D
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/build/libmlx42.a

MLX_DIR		= MLX42
LIBFT_DIR	= libft
OBJ_DIR		= objects
INCLD_DIR	= includes
SRC_DIR		= sources
RAY_DIR		= raycasting

SRC			= $(addprefix $(SRC_DIR)/, \
				main.c \
				$(RAY_SRC) \
				)

RAY_SRC		= $(addprefix $(RAY_DIR)/, \
				raycast.c \
				draw_line.c \
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

start: all
	./$(NAME)

re: fclean all

.PHONY: all clean fclean re
