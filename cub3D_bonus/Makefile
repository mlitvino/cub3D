# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 12:51:25 by mlitvino          #+#    #+#              #
#    Updated: 2025/06/09 16:47:23 by mlitvino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc -ggdb -Ofast
# -Wall -Wextra -Werror
HEADERS		= -I$(LIBFT_DIR)/$(INCLD_DIR) -I$(INCLD_DIR) -I$(MLX_DIR)/include
LIBS		= -L$(MLX_DIR)/build $(MLX) -lz -ldl -lglfw -pthread -lm -o

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

SRC			= $(addprefix $(SRC_DIR)/, \
				main.c \
				init.c \
				clean.c \
				minimap.c \
				minimap_player.c \
				minimap_utils.c \
				$(RAY_SRC) \
				$(MOV_SRC) \
				debug.c \
				)

RAY_SRC		= $(addprefix $(RAY_DIR)/, \
				raycast.c \
				find_wall.c \
				find_wall_utils.c \
				helper.c \
				raycast_utils.c \
				draw.c \
				door.c \
				sprite.c \
				sprite_init.c \
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

start: all
	./$(NAME)

re: fclean all

.PHONY: all clean fclean re



