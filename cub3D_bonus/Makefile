# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 12:51:25 by mlitvino          #+#    #+#              #
#    Updated: 2025/06/30 16:13:05 by ablodorn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc  -Wall -Wextra
# -Wall -Wextra -Werror -Ofast -march=native -flto
HEADERS		= -I$(LIBFT_DIR)/$(INCLD_DIR) -I$(INCLD_DIR)
HEADERS		+= -I$(MLX_DIR)/include -I$(RAUDIO_DIR)
LIBS		= -L$(MLX_DIR)/build $(MLX)
LIBS		+= -lz -ldl -lglfw -pthread -lm

NAME		= cub3D
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/build/libmlx42.a
RAUDIO		= $(RAUDIO_DIR)/raudio.a

OBJ_DIR		= obj
INCLD_DIR	= includes

LIBS_DIR	= ../lib
MLX_DIR		= $(LIBS_DIR)/MLX42
LIBFT_DIR	= $(LIBS_DIR)/libft
RAUDIO_DIR	=  $(LIBS_DIR)/raudio/src

SRC_DIR		= src
RAY_DIR		= raycast
MOV_DIR		= movement
MAP_DIR		= map
ENE_DIR		= enemy

SRC			= $(addprefix $(SRC_DIR)/, \
				main.c \
				init.c \
				init_mlx.c \
				init_utils.c \
				clean.c \
				audio.c \
				render.c \
				update_sprites.c \
				update_player.c \
				action.c \
				menu.c \
				minimap.c \
				minimap_player.c \
				minimap_utils.c \
				$(MAP_SRC) \
				$(RAY_SRC) \
				$(MOV_SRC) \
				$(ENE_SRC) \
				debug.c \
				)
MAP_SRC		= $(addprefix $(MAP_DIR)/, \
				perror.c \
				error.c \
				free.c \
				file_utils.c \
				read_file.c \
				map_borders.c \
				map_utils.c \
				map.c \
				surrounding.c \
				valid_file.c \
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
				door_utils.c \
				update_door.c \
				)
MOV_SRC		= $(addprefix $(MOV_DIR)/, \
				rotate.c \
				movement.c \
				event_handler.c \
				movement_utils.c \
				)
ENE_SRC		=$(addprefix $(ENE_DIR)/, \
				path.c \
				path_utils.c \
				walk.c \
				walk_utils.c \
				line_of_sight.c \
				free_enemy.c \
				wolf_action.c \
				)

OBJ			= $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))
INCLD		= $(INCLD_DIR)/cub3D.h

.SECONDARY: $(OBJ)

all: ra $(LIBFT) $(MLX) $(NAME)

ra:
	cd $(RAUDIO_DIR) && \
	cc -c raudio.c -o raudio.o \
	-I. -I../external -Wall -std=c99 \
	-DSUPPORT_MODULE_RAUDIO \
	-DRAUDIO_STANDALONE \
	-DSUPPORT_FILEFORMAT_WAV \
	-DSUPPORT_FILEFORMAT_OGG \
	-DSUPPORT_FILEFORMAT_MP3 && \
	ar rcs raudio.a raudio.o

$(MLX):
	cmake -S $(MLX_DIR) -B $(MLX_DIR)/build
	cmake --build $(MLX_DIR)/build -j6

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLD)
	@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	$(CC) $(HEADERS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.c $(INCLD)
	@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	$(CC) $(HEADERS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) $(RAUDIO_DIR)/raudio.a  $(RAUDIO_DIR)/raudio.h
	$(CC) $(OBJ) $(LIBFT) $(RAUDIO_DIR)/raudio.a  $(LIBS) $(HEADERS) -o $(NAME)

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
	./$(NAME) map/forest.cub

re: fclean all

.PHONY: all clean fclean re



