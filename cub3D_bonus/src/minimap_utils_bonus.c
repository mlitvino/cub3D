/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:46:53 by mlitvino          #+#    #+#             */
/*   Updated: 2025/07/01 17:42:27 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_d_step(t_point *p1, t_point *p2, t_point *d, t_point *step)
{
	d->x = abs(p2->x - p1->x);
	d->y = -abs(p2->y - p1->y);
	if (p1->x < p2->x)
		step->x = 1;
	else
		step->x = -1;
	if (p1->y < p2->y)
		step->y = 1;
	else
		step->y = -1;
}

void	draw_line(mlx_image_t *img, t_point *p1, t_point *p2, int color)
{
	t_point	d;
	t_point	step;
	int		err;
	int		e2;

	init_d_step(p1, p2, &d, &step);
	err = d.x + d.y;
	while (1)
	{
		mlx_put_pixel(img, p1->x, p1->y, color);
		if (p1->x == p2->x && p1->y == p2->y)
			break ;
		e2 = 2 * err;
		if (e2 >= d.y)
		{
			err += d.y;
			p1->x += step.x;
		}
		if (e2 <= d.x)
		{
			err += d.x;
			p1->y += step.y;
		}
	}
}
