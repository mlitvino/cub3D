/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 22:53:42 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/29 15:12:33 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	show_doors(t_door *list)
{
	ft_printf("---DOOR_START---\n");
	for (int i = 0; list; i++, list = list->next)
	{
		ft_printf("i: %d\n", i);

		if (list->state == CLOSED)
			ft_printf("state: CLOSED\n");
		if (list->state == OPEN)
			ft_printf("state: OPEN\n");
		if (list->state == CLOSING)
			ft_printf("state: CLOSING\n");
		if (list->state == OPENNING)
			ft_printf("state: OPENNING\n");

		ft_printf("len: %d\n", list->len);
		ft_printf("grid x %d, grid y %d\n", list->grid_x, list->grid_y);
	}
	ft_printf("----DOOR_END----\n");
}

void	show_unit_map(t_data *data)
{
	for (int j = 0; j < data->map_h * BLOCK_SIZE; j++)
	{
		ft_printf("{");
		for (int i = 0; i < data->map_w * BLOCK_SIZE; i++)
		{
			if (data->unit_map[j][i] == EMPTY)
			{
				ft_printf("%d ", data->unit_map[j][i]);
			}
			else if (data->unit_map[j][i] == WALL)
			{
				ft_printf("%s%d %s", GREEN, data->unit_map[j][i], RESET);
			}
			else if (data->unit_map[j][i] == PLAYER)
			{
				ft_printf("%s%d %s", RED, data->unit_map[j][i], RESET);
			}
			else if (data->unit_map[j][i] == DOOR)
			{
				ft_printf("%s%d %s", BLUE, data->unit_map[j][i], RESET);
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
