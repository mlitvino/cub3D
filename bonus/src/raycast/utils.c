/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:35:07 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/25 18:49:12 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	deg_rad(double deg)
{
	return (deg * M_PI / 180);
}

double	calc_dist(t_point p1, t_point p2)
{
	return (sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y
				- p2.y)));
}

uint32_t	extract_rgba(uint8_t *raw)
{
	return (*raw << 24 | *(raw + 1) << 16 | *(raw + 2) << 8 | *(raw + 3));
}

bool	is_on_map(t_data *data, t_point *p)
{
	return ((0 <= p->x && p->x < data->map_w * BLOCK_SIZE) && (0 <= p->y
			&& p->y < data->map_h * BLOCK_SIZE));
}
