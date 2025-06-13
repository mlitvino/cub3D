/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:59:38 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/13 14:55:08 by mlitvino         ###   ########.fr       */
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
	}
}

t_raycast	*init_raycast(t_data *data, t_char *player, t_raycast *raycast)
{
	int			i;

	i = 0;
	while (i < MAX_THRD)
	{
		raycast[i].data = data;
		raycast[i].player = player;
		raycast[i].door_list = data->door_list;
		raycast[i].plane = &data->plane;
		raycast[i].scr_img = data->mlx_data.scr_img;
		raycast[i].unit_map = data->unit_map;
		raycast[i].flor_rgbt = data->flor_rgb.rgbt;
		raycast[i].ceil_rgbt = data->ceil_rgb.rgbt;

		raycast[i].thread_chunk = data->rays_count / MAX_THRD;
		raycast[i].ray_angle = (player->pov.view_angl + (FOV / 2)) % 360;

		raycast[i].ray_angle -= (data->rays_angle * i * raycast[i].thread_chunk);
		if (raycast[i].ray_angle < 0)
			raycast[i].ray_angle = 360 + raycast[i].ray_angle;

		raycast[i].cur_ray = 0;
		raycast[i].view_angle = player->pov.view_angl;
		raycast[i].char_pos = player->pos;
		raycast[i].thrd_i = i;
		i++;
	}
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
