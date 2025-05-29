/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:43:06 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/30 01:30:38 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	compre_dist(t_raycast *raycast, t_wall *hor_wall, t_wall *ver_wall)
{
	if (hor_wall->dist < ver_wall->dist)
	{
		select_tex(raycast, hor_wall, HORIZONT);
		render_col(raycast, hor_wall->pos, hor_wall->dist, raycast->tex_indx);
	}
	else if (ver_wall->dist < hor_wall->dist)
	{
		select_tex(raycast, ver_wall, VERTICAL);
		render_col(raycast, ver_wall->pos, ver_wall->dist, raycast->tex_indx);
	}
	else if (hor_wall->dist != INT_MAX
		&& raycast->unit_map[hor_wall->pos.y][hor_wall->pos.x - 1] == WALL
		&& raycast->unit_map[hor_wall->pos.y][hor_wall->pos.x + 1] == WALL)
	{
		select_tex(raycast, hor_wall, HORIZONT);
		render_col(raycast, hor_wall->pos, hor_wall->dist, raycast->tex_indx);
	}
	else
	{
		select_tex(raycast, ver_wall, VERTICAL);
		render_col(raycast, ver_wall->pos, ver_wall->dist, raycast->tex_indx);
	}
}

void	cast_ray(t_raycast *raycast, double ray_angl)
{
	if ((int)ray_angl != 180 && (int)ray_angl != 0)
		find_wall(raycast, &raycast->hor_wall, HORIZONT);
	else
		raycast->hor_wall.dist = INT_MAX;
	if ((int)ray_angl != 90 && (int)ray_angl != 270)
		find_wall(raycast, &raycast->ver_wall, VERTICAL);
	else
		raycast->ver_wall.dist = INT_MAX;
	calc_norm_dist(raycast);
	compre_dist(raycast, &raycast->hor_wall, &raycast->ver_wall);
}

void	raycast(t_data *data)
{
	t_raycast	raycast;
	int			cur_ray;
	double		cur_angle;

	raycast = init_raycast(data, &data->player);
	cur_ray = 0;
	cur_angle = raycast.ray_angle;
	while (cur_ray < data->rays_count)
	{
		fill_ray_info(&raycast);
		cast_ray(&raycast, raycast.ray_angle);
		cur_ray++;
		cur_angle -= data->rays_angle;
		if (cur_angle < 0)
			cur_angle = 360 + cur_angle;
		raycast.ray_angle = cur_angle;
		raycast.cur_ray = cur_ray;
	}
}
