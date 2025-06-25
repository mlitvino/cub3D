/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:11:45 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/25 19:38:52 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_obj(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_h)
	{
		x = 0;
		while (x < data->map_w)
		{
			if (ft_strchr(DOORS, data->grid_map[y][x]))
			{
				if (create_door(data, &data->door_list, x, y) == NULL)
					clean_all(data, "malloc");
			}
			if (ft_strchr(SPRITES, data->grid_map[y][x]))
			{
				if (create_sprite(data, data->grid_map[y][x], x, y) == NULL)
					clean_all(data, "malloc");
			}
			x++;
		}
		y++;
	}
}

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
	player->ammo = PLAYER_AMMO;
	player->hp = PLAYER_HP;
	player->wall_rt = 1 + (player->height / (BLOCK_SIZE / 2));
	player->ceiling_rt = BLOCK_SIZE / (1 + ((BLOCK_SIZE / 2)
				/ (BLOCK_SIZE - player->height)));
	player->floor_rt = BLOCK_SIZE / (1 + ((BLOCK_SIZE / 2)
				/ player->height));
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
	init_mlx(data);
	init_audio(data);
	init_unit_map(data);
	init_player(data);
	init_obj(data);
	init_angle_table(data->angle_table);
	PlaySound(data->sound[S_STATUE_HUM]);
	SetSoundVolume(data->sound[S_STATUE_HUM], 0);
	SetMusicVolume(data->music[M_FOREST], 0.5);
	SetSoundVolume(data->sound[S_SHOT], 2);
	data->keys.main_button = MAIN_BUTTON;
	data->keys.pause_button = PAUSE_BUTTON;
	data->plane.center.x = WIN_W / 2;
	data->plane.center.y = WIN_H / 2;
	data->plane.dist = (WIN_W / 2) / tan(deg_rad(FOV / 2));
	data->rays_count = WIN_W;
	data->rays_angle = FOV / (double)data->rays_count;
	adjust_image_alpha(data->mlx_data.textrs_img[STATUE_FACE], 0);
}
