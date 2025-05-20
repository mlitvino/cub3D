/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:53:29 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/21 00:55:58 by mlitvino         ###   ########.fr       */
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
# define WIN_W 320
# define WIN_H 200

# define FOV 60 // field of view (angle 0-360)
# define BLOCK_SIZE 8
# define TEST_MAPX 4
# define TEST_MAPY 4

# define EMPTY 0
# define WALL 1
# define PLAYER 3


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
}				t_point;

typedef	struct	s_rgbt
{
	int	r;
	int	g;
	int	b;
	int	t;
	int	rgbt;
}				t_rgbt;

typedef struct	s_proj_plane
{
	/*
		change in resize win case
	*/
	int				width;
	int				height;
	int				dist; // 160(WIDTH/2) / tan(30)(FOV/2) = 277
	t_point			center;
}				t_proj_plane;

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

	char			grid_map[4][4];
	char			**unit_map; // 64 times bigger than map
	int				map_h;
	int				map_w;

	t_char			player;

	t_proj_plane	plane;
	int				rays_count; // 320(WIDTH_WIN)
	double			rays_angle; // FOV / rays_count
	t_rgbt			floor_rgb;
	t_rgbt			cell_rgb;
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
// double	calc_dist(t_point p1, t_point p2);

#endif
