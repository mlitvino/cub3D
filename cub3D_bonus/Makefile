# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 12:51:25 by mlitvino          #+#    #+#              #
#    Updated: 2025/06/22 17:55:13 by mlitvino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc -ggdb -Ofast -Wall -Wextra
# -Wall -Wextra -Werror
HEADERS		= -I$(LIBFT_DIR)/$(INCLD_DIR) -I$(INCLD_DIR) -I$(MLX_DIR)/include -I$(RAYLIB_DIR)
LIBS		= -L$(MLX_DIR)/build $(MLX) $(RAYLIB) -lz -ldl -lglfw -pthread -lm -o

NAME		= cub3D
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/build/libmlx42.a
RAYLIB		= $(RAYLIB_DIR)/libraylib.a

OBJ_DIR		= obj
INCLD_DIR	= includes

LIBS_DIR	= ../lib
MLX_DIR		= $(LIBS_DIR)/MLX42
LIBFT_DIR	= $(LIBS_DIR)/libft
RAYLIB_DIR	= $(LIBS_DIR)/raylib/src

SRC_DIR		= src
RAY_DIR		= raycast
MOV_DIR		= movement
MAP_DIR		= map

SRC			= $(addprefix $(SRC_DIR)/, \
				main.c \
				init.c \
				init_mlx.c \
				clean.c \
				audio.c \
				render.c \
				minimap.c \
				minimap_player.c \
				minimap_utils.c \
				$(MAP_SRC) \
				$(RAY_SRC) \
				$(MOV_SRC) \
				debug.c \
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
				valid_texture_path.c \
				doors.c \
				)

RAY_SRC		= $(addprefix $(RAY_DIR)/, \
				raycast.c \
				find_wall.c \
				check_hit.c \
				helper.c \
				raycast_utils.c \
				draw.c \
				draw_utils.c \
				door.c \
				face_enemy.c \
				sprite.c \
				sprite_init.c \
				thread.c \
				)

MOV_SRC		= $(addprefix $(MOV_DIR)/, \
				rotate.c \
				movement.c \
				event_handler.c \
				)

OBJ			= $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))
INCLD		= $(INCLD_DIR)/cub3D.h

.SECONDARY: $(OBJ)

all: $(LIBFT) $(MLX) $(RAYLIB) $(NAME)

$(RAYLIB):
	make -C $(RAYLIB_DIR)

$(MLX):
	cmake -S $(MLX_DIR) -B $(MLX_DIR)/build
	cmake --build $(MLX_DIR)/build -j6
	@cd $(MLX_DIR)/build && \
	ar x libmlx42.a glad.c.o && \
	objcopy --weaken glad.c.o && \
	ar rcs libmlx42.a *.o

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
	./$(NAME) test.cub

re: fclean all

.PHONY: all clean fclean re



