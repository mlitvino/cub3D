/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:59:38 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/21 19:07:12 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calc_norm_dist(t_raycast *raycast)
{
	double	temp;

	if (raycast->hor_wall.dist != INT_MAX)
	{
		temp = calc_dist(raycast->char_pos, raycast->hor_wall.pos);
		raycast->hor_wall.dist = temp * raycast->angl_table->beta;
	}
	if (raycast->ver_wall.dist != INT_MAX)
	{
		temp = calc_dist(raycast->char_pos, raycast->ver_wall.pos);
		raycast->ver_wall.dist = temp * raycast->angl_table->beta;
	}
}

void	select_tex(t_raycast *raycast, t_wall *wall, int axis)
{
	raycast->axis = axis;
	raycast->data->rays_dist[raycast->cur_ray] = wall->dist;
	if (wall->type == DOOR)
	{
		wall->img_i = DOOR_TEX;
		if (raycast->cur_ray == WIN_W / 2)
			raycast->player->door_facing = wall->dist;
	}
	else if (axis == VERTICAL)
	{
		if (ISEAST(raycast->ray_angle))
			wall->img_i = WEST;
		else
			wall->img_i = EAST;
	}
	else
	{
		if (ISSOUTH(raycast->ray_angle))
			wall->img_i = SOUTH;
		else
			wall->img_i = NORTH;
	}
}

void	init_common_info(t_data *data, t_char *player, t_raycast *raycast)
{
	raycast->data = data;
	raycast->player = player;
	raycast->player->door_facing = 0;
	raycast->door_list = data->door_list;
	raycast->plane = &data->plane;
	raycast->scr_img = data->mlx_data.scr_img;
	raycast->unit_map = data->unit_map;
	raycast->flor_rgbt = data->flor_rgb.rgbt;
	raycast->ceil_rgbt = data->ceil_rgb.rgbt;

}

t_raycast	*init_raycast(t_data *data, t_char *player, t_raycast *raycast)
{
	int	i;

	i = 0;
	while (i < MAX_THRD)
	{
		init_common_info(data, player, &raycast[i]);
		raycast[i].thread_chunk = data->rays_count / MAX_THRD;
		raycast[i].ray_angle = fmod((player->pov.view_angl + (FOV / 2)), 360);
		raycast[i].ray_angle -= data->rays_angle * i * raycast[i].thread_chunk;
		if (raycast[i].ray_angle < 0)
			raycast[i].ray_angle = 360 + raycast[i].ray_angle;
		raycast[i].cur_ray = 0;
		raycast[i].view_angle = player->pov.view_angl;
		raycast[i].char_pos.x = player->pos.x;
		raycast[i].char_pos.y = player->pos.y;
		raycast[i].thrd_i = i;
		i++;
	}
	return (raycast);
}

void	fill_ray_info(t_raycast *raycast)
{
	int	angle_i;

	ft_memset(&raycast->hor_wall, -1, sizeof(t_wall));
	ft_memset(&raycast->ver_wall, -1, sizeof(t_wall));
	raycast->hor_wall.dist = 0;
	raycast->ver_wall.dist = 0;
	raycast->beta = raycast->ray_angle - raycast->view_angle;
	angle_i = raycast->ray_angle * ANGLE_PRES;
	raycast->angl_table = &raycast->data->angle_table[angle_i];
	raycast->angl_table->beta = cos(deg_rad(raycast->beta));
}
