/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 22:53:42 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/19 00:52:34 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	show_unit_map(t_data *data)
{
	for (int j = 0; j < data->map_h * BLOCK_SIZE; j++)
	{
		printf("{");
		for (int i = 0; i < data->map_w * BLOCK_SIZE; i++)
		{
			if (data->unit_map[j][i] == EMPTY)
				printf("%d ", data->unit_map[j][i]);
			else if (data->unit_map[j][i] == WALL)
				printf("%s%d %s", GREEN, data->unit_map[j][i], RESET);
			else if (data->unit_map[j][i] == PLAYER)
			{
				//printf("x%dy%d", j, i);
				printf("%s%d %s", RED, data->unit_map[j][i], RESET);
			}
		}
		printf("}\n");
	}
}

void	show_char_pos(t_data *data, t_char *chr)
{
	printf("Char x: %d, y: %d\n", chr->pos.x, chr->pos.y);
}
