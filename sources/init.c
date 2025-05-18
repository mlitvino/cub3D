/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:11:45 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/19 00:58:29 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_grid_map(t_data *data)
{
	char temp_map[TEST_MAPX][TEST_MAPY] =
	{
		{0, 1, 1, 1},
		{1, 0, 1, 1},
		{1, 1, PLAYER, 1},
		{0, 1, 1, 1}
	};

	ft_memcpy(data->grid_map, temp_map, sizeof(temp_map));
}

void	init_unit_map(t_data *data)
{
	int	y;
	int	x;

	data->unit_map = ft_calloc(data->map_w * BLOCK_SIZE, sizeof(char *));
	// null check
	x = 0;
	while (x < data->map_w * BLOCK_SIZE)
	{
		data->unit_map[x] = ft_calloc(data->map_h * BLOCK_SIZE, sizeof(char));
		y = 0;
		while (y < data->map_h)
		{
			if (data->grid_map[x / BLOCK_SIZE][y] != PLAYER)
				ft_memset(&data->unit_map[x][y * BLOCK_SIZE],
					data->grid_map[x / BLOCK_SIZE][y], BLOCK_SIZE);
			y++;
		}
		x++;
	}
}

void	init_player(t_data *data)
{
	int		pos_x;
	int		pos_y;
	t_char *player;
	int		hitbox;

	player = &data->player;
	player->hitbox_radius = BLOCK_SIZE / 4;
	player->pov.fov = FOV;
	player->height = BLOCK_SIZE / 2;
	hitbox = player->hitbox_radius;

	for (int x = 0; x < TEST_MAPX; x++)
	{
		for(int y = 0; y < TEST_MAPY; y++)
		{
			if (data->grid_map[x][y] == PLAYER)
			{
				pos_x = (x * BLOCK_SIZE) + BLOCK_SIZE / 2;
				pos_y = (y * BLOCK_SIZE) + BLOCK_SIZE / 2;
			}
		}
	}
	player->pos.x = pos_x;
	player->pos.y = pos_y;

	data->unit_map[pos_x][pos_y] = PLAYER;

	for (int x = pos_x - hitbox; x <= pos_x + hitbox; x++)
		for (int y = pos_y - hitbox; y <= pos_y + hitbox; y++)
			data->unit_map[x][y] = PLAYER;
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
	t_mlx	mlx_data;

	//mlx_set_setting(MLX_STRETCH_IMAGE, true); // resize img with resizing win
	//mlx_set_setting(MLX_HEADLESS, true); // disable_win
	mlx_data.mlx_ptr = mlx_init(WIN_W, WIN_H, "cub3D", true);
	// null checker
	mlx_data.img = mlx_new_image(mlx_data.mlx_ptr, WIN_W, WIN_H);
	// null checker

	mlx_image_to_window(mlx_data.mlx_ptr, mlx_data.img, 0, 0);

	for (int x = 0; x < WIN_W; x++)
	{
		for(int y = 0; y < WIN_H; y++)
		{
			mlx_put_pixel(mlx_data.img, x, y, 0x000000FF);
		}
	}

	data->mlx_data = mlx_data;
}

void	init_data(t_data *data)
{
	init_maps(data);
	init_player(data);
	init_mlx(data);
}
