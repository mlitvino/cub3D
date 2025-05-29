/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:57:05 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/29 20:19:40 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_wall(t_point char_pos, t_dpoint *temp, double ray_angl,
		int axis_flag)
{
	if ((int)temp->h != -1)
		return ;
	if (axis_flag == VERTICAL)
	{
		temp->x = floor((double)char_pos.x / BLOCK_SIZE) * BLOCK_SIZE;
		if ((270 < ray_angl) || (ray_angl < 90))
			temp->x += BLOCK_SIZE;
		else
			temp->x -= 1;
		temp->y = (char_pos.x - temp->x) * tan(deg_rad(ray_angl));
		temp->y += char_pos.y;
	}
	else
	{
		temp->y = floor((double)char_pos.y / BLOCK_SIZE) * BLOCK_SIZE;
		if (ray_angl < 180)
			temp->y -= 1;
		else
			temp->y += BLOCK_SIZE;
		temp->x = (char_pos.y - temp->y) / tan(deg_rad(ray_angl));
		temp->x += char_pos.x;
	}
	temp->h = 1;
}

void	adjust_wall(t_dpoint *temp, double dx, double dy)
{
	if ((int)temp->h == -1)
		return ;
	temp->x += dx;
	temp->y += dy;
}

void	init_delta(int axis_flag, double *dx, double *dy, double ray_angl)
{
	if (axis_flag == VERTICAL)
	{
		*dx = BLOCK_SIZE;
		*dy = BLOCK_SIZE * tan(deg_rad(ray_angl));
		if (270 < ray_angl || ray_angl < 90)
			*dy = -*dy;
		else
			*dx = -*dx;
	}
	else
	{
		*dx = BLOCK_SIZE / tan(deg_rad(ray_angl));
		*dy = BLOCK_SIZE;
		if (ray_angl < 180)
			*dy = -*dy;
		else
			*dx = -*dx;
	}
}

void	norm_fract(t_dpoint *temp, t_wall *wall, int axis_flag,
		double ray_angl)
{
	if ((axis_flag == VERTICAL && ray_angl > 180) || axis_flag == HORIZONT
		&& (270 < ray_angl || ray_angl < 90))
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

bool	is_hit(char **unit_map, t_wall *wall)
{
	if (unit_map[wall->pos.y][wall->pos.x] == WALL)
	{
		wall->type = WALL;
		return (true);
	}
	else if (unit_map[wall->pos.y][wall->pos.x] == DOOR)
	{
		wall->type = DOOR;
		return (true);
	}
	return (false);
}

bool	find_wall(t_raycast *raycast, t_wall *wall, int axis_flag)
{
	t_dpoint	temp;
	t_point		char_pos;
	double		dx;
	double		dy;

	char_pos = raycast->char_pos;
	temp.h = -1;
	init_delta(axis_flag, &dx, &dy, raycast->ray_angle);
	while (1)
	{
		adjust_wall(&temp, dx, dy);
		init_wall(char_pos, &temp, raycast->ray_angle, axis_flag);
		norm_fract(&temp, wall, axis_flag, raycast->ray_angle);
		if (is_on_map(raycast->data, &wall->pos) == false)
		{
			wall->dist = INT_MAX;
			return (true);
		}
		if (is_hit(raycast->unit_map, wall) == true)
			return (true);
	}
	return (false);
}
