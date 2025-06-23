/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 23:08:27 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/22 20:09:22 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	edge_function(t_point a, t_point b, t_point c)
{
	return ((c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x));
}

bool	point_in_triangle(t_point p, t_point a, t_point b, t_point c)
{
	int	d1;
	int	d2;
	int	d3;

	d1 = edge_function(a, b, p);
	d2 = edge_function(b, c, p);
	d3 = edge_function(c, a, p);
	return (!(((d1 < 0) || (d2 < 0) || (d3 < 0))
			&& ((d1 > 0) || (d2 > 0) || (d3 > 0))));
}

void	norm_base(t_point *base_left, t_point *base_right,
				t_point *max, t_point *min)
{
	if (base_left->x < min->x)
		min->x = base_left->x;
	else if (base_left->x > max->x)
		max->x = base_left->x;
	if (base_left->y < min->y)
		min->y = base_left->y;
	else if (base_left->y > max->y)
		max->y = base_left->y;
	if (base_right->x < min->x)
		min->x = base_right->x;
	else if (base_right->x > max->x)
		max->x = base_right->x;
	if (base_right->y < min->y)
		min->y = base_right->y;
	else if (base_right->y > max->y)
		max->y = base_right->y;
}

void	fill_icon_with_color(mlx_image_t *minimap,
						t_point *tip, t_point *base_left, t_point *base_right)
{
	t_point	min;
	t_point	max;
	t_point	scr;

	ft_memcpy(&min, tip, sizeof(t_point));
	ft_memcpy(&max, tip, sizeof(t_point));
	norm_base(base_left, base_right, &max, &min);
	scr.y = min.y;
	while (scr.y <= max.y)
	{
		scr.x = min.x;
		while (scr.x <= max.x)
		{
			if (point_in_triangle(scr, *tip, *base_left, *base_right))
				mlx_put_pixel(minimap, scr.x, scr.y, 0xFFFFFFFF);
			scr.x++;
		}
		scr.y++;
	}
}

void	draw_player(t_data *data, int view_angle_i, mlx_image_t *minimap, t_point *mid)
{
	t_point		tip;
	t_point		base_left;
	t_point		base_right;
	int			perp_angle_i;

	tip.x = mid->x + ICON_SIZE * data->angle_table[view_angle_i].cos;
	tip.y = mid->y - ICON_SIZE * data->angle_table[view_angle_i].sin;
	perp_angle_i = (view_angle_i + 90 * ANGLE_PRES) % (360 * ANGLE_PRES);
	base_left.x = mid->x + ICON_BASE * data->angle_table[perp_angle_i].cos;
	base_left.y = mid->y - ICON_BASE * data->angle_table[perp_angle_i].sin;
	perp_angle_i = view_angle_i - 90 * ANGLE_PRES;
	if (perp_angle_i < 0)
		perp_angle_i = 360 * ANGLE_PRES + perp_angle_i;
	base_right.x = mid->x + ICON_BASE * data->angle_table[perp_angle_i].cos;
	base_right.y = mid->y - ICON_BASE * data->angle_table[perp_angle_i].sin;
	fill_icon_with_color(minimap, &tip, &base_left, &base_right);
	draw_line(minimap, &tip, &base_left, 0xFFFFFFFF);
	draw_line(minimap, &tip, &base_right, 0xFFFFFFFF);
	draw_line(minimap, &base_left, &base_right, 0xFFFFFFFF);
}
