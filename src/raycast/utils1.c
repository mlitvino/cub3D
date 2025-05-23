/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:35:07 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/23 15:43:45 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	deg_rad(double deg)
{
	return (deg * M_PI / 180);
}

double	root_dist(t_point p1, t_point p2)
{
	return (sqrt(
		(p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)
		));
}

uint32_t	extract_rgba(uint8_t *raw)
{
	return (*raw << 24 | *(raw + 1) << 16 | *(raw + 2) << 8 | *(raw + 3));
}
