/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:59:38 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/11 15:59:35 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calc_norm_dist(t_raycast *raycast)
{
	double	temp;

	if (raycast->hor_wall.dist != INT_MAX)
	{
		temp = calc_dist(raycast->char_pos, raycast->hor_wall.pos);
		raycast->hor_wall.dist = temp * cos(deg_rad(raycast->beta));
	}
	if (raycast->ver_wall.dist != INT_MAX)
	{
		temp = calc_dist(raycast->char_pos, raycast->ver_wall.pos);
		raycast->ver_wall.dist = temp * cos(deg_rad(raycast->beta));
	}
}

void	select_tex(t_raycast *raycast, t_wall *wall, int axis)
{
	if (axis == VERTICAL)
	{
		if (ISEAST(raycast->ray_angle))
			raycast->tex_indx = WEST;
		else
			raycast->tex_indx = EAST;
	}
	else
	{
		if (ISSOUTH(raycast->ray_angle))
			raycast->tex_indx = SOUTH;
		else
			raycast->tex_indx = NORTH;
	}

	if (wall->type == DOOR)
	{
		raycast->tex_indx = DOOR_TEX;

		if (raycast->cur_ray == WIN_W / 2)
		{
			raycast->player->door_facing = wall->dist;
		}
	}
}

t_raycast	init_raycast(t_data *data, t_char *player)
{
	t_raycast	raycast;

	raycast.data = data;
	raycast.player = player;
	//raycast->player.door_facing = 0;
	raycast.door_list = data->door_list;
	raycast.plane = &data->plane;
	raycast.scr_img = data->mlx_data.scr_img;
	raycast.unit_map = data->unit_map;
	raycast.flor_rgbt = data->flor_rgb.rgbt;
	raycast.ceil_rgbt = data->ceil_rgb.rgbt;
	raycast.ray_angle = (player->pov.view_angl + (FOV / 2)) % 360;
	raycast.cur_ray = 0;
	raycast.view_angle = player->pov.view_angl;
	raycast.char_pos = player->pos;
	return (raycast);
}

void	fill_ray_info(t_raycast *raycast)
{
	ft_memset(&raycast->hor_wall, -1, sizeof(t_wall));
	ft_memset(&raycast->ver_wall, -1, sizeof(t_wall));
	raycast->hor_wall.dist = 0;
	raycast->ver_wall.dist = 0;
	raycast->beta = raycast->ray_angle - raycast->view_angle;
}
