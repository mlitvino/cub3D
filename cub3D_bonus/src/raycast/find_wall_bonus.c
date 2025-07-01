/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wall_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:57:05 by mlitvino          #+#    #+#             */
/*   Updated: 2025/07/01 17:42:27 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_wall(t_raycast *raycast, t_dpoint *temp,
			t_point *char_pos, int axis)
{
	if ((int)temp->h != -1)
		return ;
	if (axis == VERTICAL)
	{
		temp->x = floor((double)char_pos->x / BLOCK_SIZE) * BLOCK_SIZE;
		if (270 < raycast->ray_angle || raycast->ray_angle < 90)
			temp->x += BLOCK_SIZE;
		else
			temp->x -= 1;
		temp->y = (char_pos->x - temp->x) * raycast->angl_table->tan;
		temp->y += char_pos->y;
	}
	else
	{
		temp->y = floor((double)char_pos->y / BLOCK_SIZE) * BLOCK_SIZE;
		if (raycast->ray_angle < 180)
			temp->y -= 1;
		else
			temp->y += BLOCK_SIZE;
		temp->x = (char_pos->y - temp->y) / raycast->angl_table->tan;
		temp->x += char_pos->x;
	}
	temp->h = 1;
}

void	adjust_wall(t_raycast *raycast, t_dpoint *temp)
{
	if ((int)temp->h == -1)
		return ;
	temp->x += raycast->dx;
	temp->y += raycast->dy;
}

void	init_delta(t_raycast *raycast, int axis)
{
	double	ray_angl;

	ray_angl = raycast->ray_angle;
	if (axis == VERTICAL)
	{
		raycast->dx = BLOCK_SIZE;
		raycast->dy = BLOCK_SIZE * raycast->angl_table->tan;
		if (270 < raycast->ray_angle || raycast->ray_angle < 90)
			raycast->dy = -raycast->dy;
		else
			raycast->dx = -raycast->dx;
	}
	else
	{
		raycast->dx = BLOCK_SIZE / raycast->angl_table->tan;
		raycast->dy = BLOCK_SIZE;
		if (ray_angl < 180)
			raycast->dy = -raycast->dy;
		else
			raycast->dx = -raycast->dx;
	}
}

void	norm_fract(t_dpoint *temp, t_wall *wall, int axis, double ray_angl)
{
	if ((axis == VERTICAL && ray_angl > 180)
		|| (axis == HORIZONT
			&& (270 < ray_angl || ray_angl < 90)))
	{
		wall->pos.x = temp->x;
		wall->pos.y = temp->y;
	}
	else
	{
		wall->pos.x = ceil(temp->x);
		wall->pos.y = ceil(temp->y);
	}
}

bool	find_wall(t_raycast *raycast, t_wall *wall, int axis)
{
	t_dpoint	temp;

	temp.h = -1;
	temp.x = -1;
	temp.y = -1;
	init_delta(raycast, axis);
	while (1)
	{
		adjust_wall(raycast, &temp);
		init_wall(raycast, &temp, &raycast->char_pos, axis);
		norm_fract(&temp, wall, axis, raycast->ray_angle);
		if (is_on_map(raycast->data, &wall->pos) == false)
		{
			wall->dist = INT_MAX;
			return (true);
		}
		if (check_hit(raycast, wall, axis) == true)
			return (true);
	}
	return (false);
}
