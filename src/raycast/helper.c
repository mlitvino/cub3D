/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:59:38 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/25 19:00:21 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	calc_norm_dist(t_raycast *raycast)
{
	double	temp;

	if (raycast->hor_dist != INT_MAX)
	{
		temp = calc_dist(raycast->char_pos, raycast->hor_wall);
		raycast->hor_dist = temp * cos(deg_rad(raycast->beta));
	}
	if (raycast->ver_dist != INT_MAX)
	{
		temp = calc_dist(raycast->char_pos, raycast->ver_wall);
		raycast->ver_dist = temp * cos(deg_rad(raycast->beta));
	}
}

void	select_tex(t_raycast *raycast, int axis_flag)
{
	if (axis_flag == VERTICAL)
	{
		if (90 < raycast->ray_angle && raycast->ray_angle < 270)
			raycast->tex_indx = EAST;
		else
			raycast->tex_indx = WEST;
	}
	else
	{
		if (raycast->ray_angle < 180)
			raycast->tex_indx = SOUTH;
		else
			raycast->tex_indx = NORTH;
	}
}

t_raycast	init_raycast(t_data *data, t_char *player)
{
	t_raycast	raycast;

	raycast.data = data;
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
	ft_memset(&raycast->hor_wall, -1, sizeof(t_point));
	ft_memset(&raycast->ver_wall, -1, sizeof(t_point));
	raycast->hor_dist = 0;
	raycast->ver_dist = 0;
	raycast->beta = raycast->ray_angle - raycast->view_angle;
}
