# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 12:51:25 by mlitvino          #+#    #+#              #
#    Updated: 2025/07/01 17:44:07 by mlitvino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc  -Wall -Wextra -Werror -Ofast -march=native -flto
HEADERS		= -I$(LIBFT_DIR)/$(INCLD_DIR) -I$(INCLD_DIR)
HEADERS		+= -I$(MLX_DIR)/include -I$(RAUDIO_DIR)
LIBS		= -L$(MLX_DIR)/build $(MLX) $(RAUDIO)
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
				main_bonus.c \
				init_bonus.c \
				init_mlx_bonus.c \
				init_utils_bonus.c \
				clean_bonus.c \
				audio_bonus.c \
				render_bonus.c \
				update_sprites_bonus.c \
				update_player_bonus.c \
				action_bonus.c \
				menu_bonus.c \
				minimap_bonus.c \
				minimap_player_bonus.c \
				minimap_utils_bonus.c \
				$(MAP_SRC) \
				$(RAY_SRC) \
				$(MOV_SRC) \
				$(ENE_SRC) \
				)
MAP_SRC		= $(addprefix $(MAP_DIR)/, \
				perror_bonus.c \
				error_bonus.c \
				free_bonus.c \
				file_utils_bonus.c \
				read_file_bonus.c \
				map_borders_bonus.c \
				map_utils_bonus.c \
				map_bonus.c \
				surrounding_bonus.c \
				valid_file_bonus.c \
				doors_bonus.c \
				)
RAY_SRC		= $(addprefix $(RAY_DIR)/, \
				raycast_bonus.c \
				find_wall_bonus.c \
				check_hit_bonus.c \
				helper_bonus.c \
				raycast_utils_bonus.c \
				draw_bonus.c \
				draw_utils_bonus.c \
				door_bonus.c \
				face_enemy_bonus.c \
				sprite_bonus.c \
				sprite_init_bonus.c \
				thread_bonus.c \
				door_utils_bonus.c \
				update_door_bonus.c \
				)
MOV_SRC		= $(addprefix $(MOV_DIR)/, \
				rotate_bonus.c \
				movement_bonus.c \
				event_handler_bonus.c \
				movement_utils_bonus.c \
				)
ENE_SRC		=$(addprefix $(ENE_DIR)/, \
				path_bonus.c \
				path_utils_bonus.c \
				walk_bonus.c \
				walk_utils_bonus.c \
				line_of_sight_bonus.c \
				free_enemy_bonus.c \
				wolf_action_bonus.c \
				)

OBJ			= $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))
INCLD		= $(INCLD_DIR)/cub3D_bonus.h

.SECONDARY: $(OBJ)

all: $(RAUDIO) $(LIBFT) $(MLX) $(NAME)

$(RAUDIO):
	cd $(RAUDIO_DIR) && \
	cc -c raudio.c -o raudio.o \
	-I. -I../external -Wall -std=c99 \
	-DSUPPORT_MODULE_RAUDIO \
	-DRAUDIO_STANDALONE \
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

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) $(LIBS) $(HEADERS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) all
	make -C $(LIBFT_DIR) bonus

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(RAUDIO_DIR)/raudio.o
	make -C $(LIBFT_DIR) clean

fclean: clean
	make -C $(MLX_DIR)/build clean
	make -C $(LIBFT_DIR) fclean
	rm -rf $(RAUDIO)
	rm -f $(NAME)

start: all
	./$(NAME) map/forest.cub

re: fclean all

.PHONY: all clean fclean re



