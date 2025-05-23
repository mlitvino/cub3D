/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 22:53:42 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/23 17:32:29 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	show_unit_map(t_data *data)
{
	for (int j = 0; j < data->map_h * BLOCK_SIZE; j++)
	{
		ft_printf("{");
		for (int i = 0; i < data->map_w * BLOCK_SIZE; i++)
		{
			if (data->unit_map[j][i] == EMPTY)
				ft_printf("%d ", data->unit_map[j][i]);
			else if (data->unit_map[j][i] == WALL)
				ft_printf("%s%d %s", GREEN, data->unit_map[j][i], RESET);
			else if (data->unit_map[j][i] == PLAYER)
			{
				//ft_printf("x%dy%d", j, i);
				ft_printf("%s%d %s", RED, data->unit_map[j][i], RESET);
			}
		}
		ft_printf("}\n");
	}
}

void	show_char_pos(t_data *data, t_char *chr)
{
	ft_printf("Char x: %d, y: %d\n", chr->pos.x, chr->pos.y);
}

void	show_redline(t_data *data)
{
	for (int y = 0; y < data->mlx_data.scr_img->height; y++)
		mlx_put_pixel(data->mlx_data.scr_img, data->plane.center.x, y, 0xFF0000FF);
}
