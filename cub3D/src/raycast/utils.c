/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:35:07 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/26 14:47:39 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	deg_rad(double deg)
{
	return (deg * M_PI / 180);
}

long double	calc_dist(t_point p1, t_point p2)
{
	long double	dx;
	long double	dy;
	long double	dist;

	dy = (long double)p1.y - (long double)p2.y;
	dx = (long double)p1.x - (long double)p2.x;
	dist = dx * dx + dy * dy;
	if (dist > LDBL_MAX)
		dist = LDBL_MAX;
	return (sqrtl(dist));
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
