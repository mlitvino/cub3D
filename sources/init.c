/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:11:45 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/17 23:30:16 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_grid_map(t_data *data)
{
	char temp_map[TEST_MAPX][TEST_MAPY] =
	{
		{0, 1, 1, 1},
		{1, 0, 0, 1},
		{1, 0, PLAYER, 1},
		{0, 1, 1, 1}
	};

	ft_memcpy(data->grid_map, temp_map, sizeof(temp_map));
}

void	init_unit_map(t_data *data)
{
	int	row;
	int	col;

	data->unit_map = ft_calloc(data->map_w * BLOCK_SIZE, sizeof(char *));
	// null check
	col = 0;
	while (col < data->map_w * BLOCK_SIZE)
	{
		data->unit_map[col] = ft_calloc(data->map_h * BLOCK_SIZE, sizeof(char));
		row = 0;
		while (row < data->map_h)
		{
			if (data->grid_map[col / BLOCK_SIZE][row] != PLAYER)
				ft_memset(&data->unit_map[col][row * BLOCK_SIZE],
					data->grid_map[col / BLOCK_SIZE][row], BLOCK_SIZE);
			row++;
		}
		col++;
	}
}

void	init_player(t_data *data)
{
	for (int i = 0; i < TEST_MAPX; i++)
	{
		for(int j = 0; j < TEST_MAPY; j++)
		{
			if (data->grid_map[i][j] == PLAYER)
				{
					data->player.pos.x = (i * BLOCK_SIZE) + BLOCK_SIZE / 2;
					data->player.pos.y = (j * BLOCK_SIZE) + BLOCK_SIZE / 2;
				}
		}
	}

	data->player.height = BLOCK_SIZE / 2;
}

void	init_maps(t_data *data)
{
	init_grid_map(data);
	data->map_h = TEST_MAPY;
	data->map_w = TEST_MAPX;
	init_unit_map(data);
}

void	init_mlx(t_data *data)
{
	t_mlx_data	mlx_data;

	mlx_data.mlx_ptr = mlx_init(WIN_W, WIN_H, "cub3D", true);
	// null checker
	data->mlx_data = mlx_data;
}

void	init_data(t_data *data)
{
	init_maps(data);
	init_player(data);
	init_mlx(data);
}
