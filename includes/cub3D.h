/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:53:29 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/14 17:53:03 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "MLX42/MLX42_Int.h"
#include "libft.h"
#include <stdio.h>

# define FOV 60

typedef struct	s_vectr
{
	int	x;
	int	y;
}				t_vectr;

typedef struct	s_data
{
	int		map[4][4];

	int		rays_count;// = WIDTH_WIN
	int		floor_rgb;
	int		cell_rgb;
}				t_data;

#endif
