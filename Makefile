# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 12:51:25 by mlitvino          #+#    #+#              #
#    Updated: 2025/05/13 18:19:54 by mlitvino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
# -Wall -Wextra -Werror
CFLAGS		= -I$(LIBFT_DIR)/$(INCLD_DIR) -I$(INCLD_DIR) -I$(MLX_DIR)/include
LIBFLAG		= -L$(MLX_DIR)/build $(MLX) -L/usr/lib -lXext -lX11 -lm -lz -ldl -lglfw -pthread -lm -o

NAME		= cub3D
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_GIT	= https://github.com/mlitvino/libft.git
MLX			= $(MLX_DIR)/build/libmlx42.a
MLX_GIT		= https://github.com/codam-coding-college/MLX42.git

SRC_DIR		= sources
OBJ_DIR		= objects
LIBFT_DIR	= libft
INCLD_DIR	= includes
MLX_DIR		= MLX42

SRC			= $(addprefix $(SRC_DIR)/, \
				main.c)
OBJ			= $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))
INCLD		= $(INCLD_DIR)/cub3D.h

.SECONDARY: $(OBJ)

all: $(MLX) $(LIBFT) $(NAME)

$(MLX):
	cmake -S $(MLX_DIR) -B $(MLX_DIR)/build
	cmake --build $(MLX_DIR)/build -j6

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLD)
	@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.c $(INCLD)
	@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) $(LIBFLAG) $@

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
