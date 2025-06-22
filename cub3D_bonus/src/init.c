/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:11:45 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/22 18:49:44 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_unit_map(t_data *data)
{
	int	y;
	int	x;

	data->unit_map = ft_calloc(data->map_h * BLOCK_SIZE, sizeof(char *));
	if (!data->unit_map)
		clean_all(data, "malloc");
	y = 0;
	while (y < data->map_h * BLOCK_SIZE)
	{
		data->unit_map[y] = ft_calloc(data->map_w * BLOCK_SIZE, sizeof(char));
		if (!data->unit_map[y])
			clean_all(data, "malloc");
		x = 0;
		while (x < data->map_w)
		{
			ft_memset(&data->unit_map[y][x * BLOCK_SIZE], data->grid_map[y
				/ BLOCK_SIZE][x], BLOCK_SIZE);
			x++;
		}
		y++;
	}
}

void	init_player(t_data *data)
{
	t_char	*player;

	player = &data->player;
	player->data = data;
	player->hitbox_radius = BLOCK_SIZE / 4;
	player->pov.fov = FOV;
	player->height = BLOCK_SIZE / 2;
	player->move_spd = BLOCK_SIZE / 16;
	player->turn_spd = 2;
	printf("x %d y %d\n", data->map_h, data->map_w);
	for (int y = 0; y < data->map_h; y++)
	{
		for (int x = 0; x < data->map_w; x++)
		{
			if (data->grid_map[y][x] == DOOR)
			{
				if (create_door(&data->door_list, x, y) == NULL)
					clean_all(data, "malloc"); // IMRPOVE
			}
			if (data->grid_map[y][x] == WOLF)
			{
				if (create_sprite(data, WOLF, x, y) == NULL)
					clean_all(data, "malloc"); // IMRPOVE
			}
			if (data->grid_map[y][x] == STATUE)
			{
				if (create_sprite(data, STATUE, x, y) == NULL)
					clean_all(data, "malloc"); // IMRPOVE
			}
			// if (data->grid_map[y][x] == LAMP)
			// {
			// 	if (create_sprite(&data->door_list, LAMP, x, y) == NULL)
			// 		clean_all(data, "malloc"); // IMRPOVE
			// }
		}
	}
}

void	init_angle_table(t_table *angle_table)
{
	int		total;
	double	deg;
	double	rad;
	int		i;

	i = 0;
	total = ANGLE_PRES * 360;
	while (i < total)
	{
		deg = (double)i / ANGLE_PRES;
		rad = DEG_TO_RAD(deg);
		angle_table[i].sin = sin(rad);
		angle_table[i].cos = cos(rad);
		angle_table[i].tan = tan(rad);
		i++;
	}
}

void	init_data(t_data *data)
{
	data->game_state = START;
	init_audio(data);
	init_mlx(data);
	init_unit_map(data);
	init_player(data);
	init_angle_table(data->angle_table);
	data->main_button = MAIN_BUTTON;
	data->pause_button = PAUSE_BUTTON;
	data->plane.center.x = WIN_W / 2;
	data->plane.center.y = WIN_H / 2;
	data->plane.dist = (WIN_W / 2) / tan(deg_rad(FOV / 2));
	data->rays_count = WIN_W;
	data->rays_angle = FOV / (double)data->rays_count;
	adjust_image_alpha(data->mlx_data.textrs_img[STATUE_FACE], 0);
}
