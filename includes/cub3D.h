/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:53:29 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/15 18:02:50 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "MLX42/MLX42_Int.h"
#include "libft.h"
#include <stdio.h>

# define PLAYER_FOV 60 // field of view (angle 0-360)
# define BLOCK_SIZE 64

# define EMPTY 0
# define WALL 1

typedef struct	s_data t_data;

typedef	struct	s_trgb
{
	int	t;
	int	r;
	int	g;
	int	b;
}				t_trgb;

typedef struct	s_vector
{
	int	x;
	int	y;
}				t_vector;

typedef struct	s_pov
{
	t_vector	char_pos;
	t_vector	view_pos;
	int			angle; // = FOV
}				t_pov; // point of view

typedef struct	s_char
{
	t_data	*data;

	t_pov	pov;
	int		height; // BLOCK_SIZE / 2
}				t_char ;// characters(npc, player)

typedef struct	s_data
{
	int			grid_map[4][4];
	int			*unit_map; // 64 times bigger than map

	t_char		player;

	int			plane_dimen[2]; // [0] - WIDTH_WIN [1] - HEIGHT_WIN
	int			plane_dist; // 160 / tan(30) = 277
	t_vector	plane_cntr;

	int			rays_count;// = WIDTH_WIN
	int			rays_angle; // FOV / rays_count

	t_trgb		floor_rgb;
	t_trgb		cell_rgb;
}				t_data;

#endif
