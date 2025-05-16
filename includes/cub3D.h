/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:53:29 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/16 18:07:15 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "MLX42/MLX42_Int.h"
#include "libft.h"
#include <stdio.h>
#include <errno.h>

# define BPP sizeof(int32_t)

# define PLAYER_FOV 60 // field of view (angle 0-360)
# define BLOCK_SIZE 64
# define MAPX 4
# define MAPY 4

# define EMPTY 0
# define WALL 1

typedef struct	s_data t_data;

typedef	struct	s_rgbt
{
	int	r;
	int	g;
	int	b;
	int	t;
	int	rgbt;
}				t_rgbt;

typedef struct	s_point
{
	int	x;
	int	y;
	int	height;
}				t_point;

typedef struct	s_pov
{
	t_point		char_pos;
	t_point		view_pos;
	int			field_angl; // = FOV

}				t_pov; // point of view

typedef struct	s_char
{
	t_data			*data;

	t_pov			pov;
	int				height; // BLOCK_SIZE / 2
	int				hitbox_radius;

	
	int				move_spd; // units
	int				turn_spd; // angle
}				t_char; // characters(npc, player)

typedef struct	s_proj_plane
{
	int				dimen[2]; // [0] - WIDTH_WIN [1] - HEIGHT_WIN
	int				dist; // 160(WIDTH/2) / tan(30)(FOV/2) = 277
	t_point			center;
}				t_proj_plane;

typedef struct	s_data
{
	int				grid_map[4][4];
	int				*unit_map; // 64 times bigger than map

	t_point			char_pos;
	t_char			player;

	t_proj_plane	plane;
	int				rays_count; // 320(WIDTH_WIN)
	int				rays_angle; // FOV / rays_count

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

#endif
