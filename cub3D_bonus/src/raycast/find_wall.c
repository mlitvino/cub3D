/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:57:05 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/11 15:00:42 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_wall(t_point char_pos, t_dpoint *temp, double ray_angl,
		int axis)
{
	if ((int)temp->h != -1)
		return ;
	if (axis == VERTICAL)
	{
		temp->x = floor((double)char_pos.x / BLOCK_SIZE) * BLOCK_SIZE;
		if (ISEAST(ray_angl))
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
		raycast->dy = BLOCK_SIZE * tan(deg_rad(ray_angl));
		if (ISEAST(ray_angl))
			raycast->dy = -raycast->dy;
		else
			raycast->dx = -raycast->dx;
	}
	else
	{
		raycast->dx = BLOCK_SIZE / tan(deg_rad(ray_angl));
		raycast->dy = BLOCK_SIZE;
		if (ISNORTH(ray_angl))
			raycast->dy = -raycast->dy;
		else
			raycast->dx = -raycast->dx;
	}
}

void	norm_fract(t_dpoint *temp, t_wall *wall, int axis,
		double ray_angl)
{
	if ((axis == VERTICAL && ray_angl > 180) || axis == HORIZONT
		&& ISEAST(ray_angl))
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

void	set_direct(t_door *door, int axis, double ray_angle)
{
	if (axis == VERTICAL)
	{
		if (ISEAST(ray_angle))
			door->direct = EAST;
		else
			door->direct = WEST;
	}
	else
	{
		if (ISNORTH(ray_angle))
			door->direct = NORTH;
		else
			door->direct = SOUTH;
	}
}

bool	extend_door(t_raycast *raycast, t_wall *wall, int axis)
{
	t_door		*door;
	t_dpoint	temp;
	int			offset;

	door = find_door(raycast->door_list , wall->pos.x, wall->pos.y);
	//set_direct(door, axis, raycast->ray_angle); // is needed?
	wall->door_len = door->len;


	temp.x = wall->pos.x;
	temp.y = wall->pos.y;

	temp.x += raycast->dx / 2;
	temp.y += raycast->dy / 2;

	if (is_on_map(raycast->data, &(t_point){(int)temp.x, (int)temp.y}) == false)
		return (false);

	if (axis == VERTICAL)
		offset = (int)temp.y % BLOCK_SIZE;
	else
		offset = (int)temp.x % BLOCK_SIZE;

	if (raycast->unit_map[(int)temp.y][(int)temp.x] == DOOR
		&& door->len > offset)
	{
		wall->pos.x = temp.x;
		wall->pos.y = temp.y;
		return (true);
	}
	return (false);
}

bool	check_hit(t_raycast *raycast, t_wall *wall, int axis)
{
	if (raycast->unit_map[wall->pos.y][wall->pos.x] == WALL)
	{
		wall->type = WALL;
		return (true);
	}
	else if (raycast->unit_map[wall->pos.y][wall->pos.x] == DOOR)
	{
		if (extend_door(raycast, wall, axis) == true)
		{
			wall->type = DOOR;
			return (true);
		}
	}
	return (false);
}

bool	find_wall(t_raycast *raycast, t_wall *wall, int axis)
{
	t_dpoint	temp;
	t_point		char_pos;

	char_pos = raycast->char_pos;
	temp.h = -1;
	init_delta(raycast, axis);
	while (1)
	{
		adjust_wall(raycast, &temp);
		init_wall(char_pos, &temp, raycast->ray_angle, axis);
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
