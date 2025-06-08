/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:39:09 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/08 23:11:52 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void draw_line(mlx_image_t *img, t_point p1, t_point p2, int color)
{
	int dx = abs(p2.x - p1.x), sx = p1.x < p2.x ? 1 : -1;
	int dy = -abs(p2.y - p1.y), sy = p1.y < p2.y ? 1 : -1;
	int err = dx + dy, e2;

	while (1)
	{
		mlx_put_pixel(img, p1.x, p1.y, color);
		if (p1.x == p2.x && p1.y == p2.y)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			p1.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			p1.y += sy;
		}
	}
}

void	put_minimap_pix(t_data *data, t_point map_pos, int x, int y)
{
	if (is_on_map(data, &map_pos) == true)
	{
		if (data->unit_map[map_pos.y][map_pos.x] == WALL)
			mlx_put_pixel(data->mlx_data.minimap, x, y, 0xFF0000FF);
		// else if (data->unit_map[map_pos.y][map_pos.x] == DOOR)
		// 	mlx_put_pixel(data->mlx_data.minimap, x, y, 0xFF0000FF);
	}
}

void	draw_background(mlx_image_t *minimap)
{
	int	x;
	int	y;

	x = 0;
	while (x < minimap->width)
	{
		y = 0;
		while (y < minimap->height)
		{
			mlx_put_pixel(minimap, x, y, 0xFF);
			y++;
		}
		x++;
	}
}

void	draw_obj(t_data *data, t_point *mid_img, mlx_image_t *minimap)
{
	int		x;
	int		y;
	t_point map_pos;
	int		step;

	step = BLOCK_SIZE / SCALE;
	map_pos.x = data->player.pos.x - (mid_img->x * step);
	x = 0;
	while (x < minimap->width)
	{
		y = 0;
		map_pos.y = data->player.pos.y - (mid_img->y * step);
		while (y < minimap->height)
		{
			put_minimap_pix(data, map_pos, x, y);
			map_pos.y += step;
			y++;
		}
		map_pos.x += step;
		x++;
	}
}

void	draw_minimap(t_data *data, mlx_image_t *minimap, char **unit_map, t_point char_pos)
{
	t_point	mid_img;

	mid_img.x = minimap->width / 2;
	mid_img.y = minimap->height / 2;
	draw_background(minimap);
	draw_player(data->player.pov.view_angl, minimap, mid_img.x, mid_img.y);
	draw_obj(data, &mid_img, minimap);
}
