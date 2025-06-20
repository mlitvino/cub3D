/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:39:09 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/20 23:09:24 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_minimap_pix(t_data *data, t_point map_pos, int x, int y)
{
	if (is_on_map(data, &map_pos) == true)
	{
		if (data->unit_map[map_pos.y][map_pos.x] == WALL)
			mlx_put_pixel(data->mlx_data.minimap, x, y, GREEN_COL);
		// else if (data->unit_map[map_pos.y][map_pos.x] == DOOR)
		// 	mlx_put_pixel(data->mlx_data.minimap, x, y, 0xFF0000FF);
	}
}

void	draw_background(mlx_image_t *minimap)
{
	uint32_t 	x;
	uint32_t 	y;

	x = 0;
	while (x < minimap->width)
	{
		y = 0;
		while (y < minimap->height)
		{
			mlx_put_pixel(minimap, x, y, 0xAA);
			y++;
		}
		x++;
	}
}

void	draw_obj(t_data *data, t_point *mid_img, mlx_image_t *minimap)
{
	uint32_t		x;
	uint32_t		y;
	t_point	map_pos;
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

void	draw_minimap(t_data *data, mlx_image_t *minimap)
{
	t_point	mid_img;

	mid_img.x = minimap->width / 2;
	mid_img.y = minimap->height / 2;
	draw_background(minimap);
	draw_player(data->player.pov.view_angl, minimap, mid_img.x, mid_img.y);
	draw_obj(data, &mid_img, minimap);
}
