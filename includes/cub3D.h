/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:53:29 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/23 13:30:50 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "MLX42/MLX42_Int.h"
#include "libft.h"
#include <stdio.h>
#include <errno.h>
#include <math.h>

# define BPP sizeof(int32_t)

# define WIN_W 1600
# define WIN_H 1000

# define FOV 50 // field of view (angle 0-360)
# define BLOCK_SIZE 64
# define TEST_MAPX 6
# define TEST_MAPY 4

# define EMPTY 0
# define WALL 1
# define PLAYER 3

//Movement
#define DEG_TO_RAD(a) ((a) * M_PI / 180.0) // convert degree to radiant to be used for cos/sin
#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_LEFT_ARROW 65361
#define KEY_RIGHT_ARROW 65363
#define KEY_ESC 65307


enum
{
	NORTH,
	EAST,
	WEST,
	SOUTH,
	MAX_TEX,
};

typedef struct	s_data t_data;

//------------------------------TEST----------------------------------
# define RESET   "\033[0m"
# define BLACK   "\033[30m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"

//------------------------------Graphic----------------------------------

typedef struct	s_point
{
	int	x;
	int	y;
	int	height;
	int	inval;
}				t_point;

typedef	struct	s_rgbt
{
	int	r;
	int	g;
	int	b;
	int	t;
	int	rgbt;
}				t_rgbt;

typedef struct	s_project
{
	/*
		change in resize win case
	*/
	int				width;
	int				height;
	int				dist; // 160(WIDTH/2) / tan(30)(FOV/2) = 277
	t_point			center;
}				t_project;

//-------------------------------GAME------------------------------------
typedef struct	s_pov
{
	t_point		view_pos;
	int			view_angl;
	int			fov; // = FOV

}				t_pov; // point of view

typedef struct	s_char
{
	t_data			*data;

	t_pov			pov;
	int				height; // BLOCK_SIZE / 2

	int				hitbox_radius;
	t_point			pos;

	int				move_spd; // units
	int				turn_spd; // angle
}				t_char; // characters(npc, player)

//-------------------------------GENERAL------------------------------------

typedef struct	s_mlx
{
	mlx_t			*mlx_ptr;

	mlx_image_t		*scr_img;

	mlx_texture_t	*textrs[MAX_TEX];
	mlx_image_t		*textrs_img[MAX_TEX];
}				t_mlx;

typedef struct	s_data
{
	t_mlx		mlx_data;

	char		grid_map[TEST_MAPY][TEST_MAPX];
	char		**unit_map; // 64 times bigger than map
	int			map_h;
	int			map_w;

	t_char		player;

	t_project	plane;
	int			rays_count; // 320(WIDTH_WIN)
	double		rays_angle; // FOV / rays_count
	t_rgbt		floor_rgb;
	t_rgbt		cell_rgb;
}				t_data;


//TEMP
typedef struct s_2dpoint
{
	double	x;
	double	y;
	double	h;
	int		color;
}	t_2dpoint;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		gradient;
	double	t;
}	t_color;

typedef struct s_delta
{
	double	dx;
	double	dy;
}	t_delta;
//END_TEMP

//-------------------------------RAYCASTING------------------------------------
// draw_line.c
void	draw_line(t_data *data, t_2dpoint p0, t_2dpoint p1);

// clean.c
void	clean_map(t_data *data);
void	clean_mlx(t_data *data);
void	clean_all(t_data *data);

// init.c
void	init_grid_map(t_data *data);
void	init_unit_map(t_data *data);
void	init_maps(t_data *data);
void	init_mlx(t_data *data);
void	init_data(t_data *data);

// debug.c
void	show_char_pos(t_data *data, t_char *chr);
void	show_unit_map(t_data *data);

// raycast.c
void	raycast(t_data *data);

// utils1.c
double	deg_rad(double deg);
double	root_dist(t_point p1, t_point p2);

//-------------------------------MOVEMENT------------------------------------
void key_event_handler(mlx_key_data_t keydata, void *param);
void move_player(t_char *player, double angle_offset);
int check_for_wall_collision(t_char *player, double new_x, double new_y);
void rotate_player_right(t_char *player);
void rotate_player_left(t_char *player);

#endif
