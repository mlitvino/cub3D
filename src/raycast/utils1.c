/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:35:07 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/20 19:06:47 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	deg_rad(double deg)
{
	return (deg * (M_PI / 180));
}

double	calc_dist(t_point p1, t_point p2)
{
	return (sqrt(
		(p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p2.y) * (p2.y - p2.y)
		));
}
