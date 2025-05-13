/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:53:29 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/13 18:05:11 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "glad/glad.h"
#include "KHR/khrplatform.h"
#include "lodepng/lodepng.h"
#include "MLX42/MLX42_Int.h"
#include "MLX42/MLX42.h"

#include "libft.h"

#include <stdio.h>

typedef struct	s_data
{
	char	ptr;
	int		floor_rgb;
	int		cell_rgb;
}				t_data;

#endif
