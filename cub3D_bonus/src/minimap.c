/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:39:09 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/06 19:42:08 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

# define SCALE 10
# define RAD 10

void	draw_minimap(t_data *data, mlx_image_t *minimap, char **unit_map, t_point char_pos)
{
	int	x;
	int	y;
	t_point map_pos;
	int		step;


	for (int x = 0; x < minimap->width; x++)
		for(int y = 0; y < minimap->height; y++)
			mlx_put_pixel(minimap, x, y, 0x000000FF); // BLACK

	x = 0;
	step = BLOCK_SIZE / SCALE;
	map_pos.x = char_pos.x - (SCALE * BLOCK_SIZE);
	while (x < minimap->width)
	{
		y = 0;
		map_pos.y = char_pos.y - (SCALE * BLOCK_SIZE);
		while (y < minimap->height)
		{
			if (is_on_map(data, &map_pos) == true)
			{
				if (unit_map[map_pos.y][map_pos.x] == WALL)
				{
					mlx_put_pixel(minimap, x, y, 0xFF0000FF);
				}
			}
			if (x == minimap->width / 2 && y == minimap->height / 2)
			{
				//printf("HERE\n"); //del
				for (int max_y = y + RAD; y <= max_y + step; y++)
					for (int max_x = x + RAD; x <= max_x + step; x++)
						mlx_put_pixel(minimap, x, y, 0xFFFFFFFF);
			}
			map_pos.y += step;
			y++;
		}
		map_pos.x += step;
		x++;
	}
}
