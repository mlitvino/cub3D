/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:24:42 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/24 23:54:37 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_on_map(t_data *data, t_point *p)
{
	return ((0 <= p->x && p->x < data->map_w * BLOCK_SIZE)
			&& (0 <= p->y && p->y < data->map_h * BLOCK_SIZE));
}

bool	extend_door(t_raycast *raycast, t_wall *wall, int axis)
{
	t_door		*door;
	t_point		temp;
	int			offset;

	door = find_door(raycast->door_list, wall->pos.x, wall->pos.y);
	wall->door_len = door->len;
	temp.x = wall->pos.x + raycast->dx / 2;
	temp.y = wall->pos.y + raycast->dy / 2;
	if (is_on_map(raycast->data, &temp) == false)
		return (false);
	if (axis == VERTICAL)
		offset = temp.y % BLOCK_SIZE;
	else
		offset = temp.x % BLOCK_SIZE;
	if (ft_strchr(DOORS, raycast->unit_map[temp.y][temp.x])
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
	int	unit_point;

	unit_point = raycast->unit_map[wall->pos.y][wall->pos.x];
	if (ft_strchr(WALLS, unit_point))
	{
		wall->type = unit_point;
		return (true);
	}
	else if (ft_strchr(DOORS, unit_point))
	{
		if (extend_door(raycast, wall, axis) == true)
		{
			wall->type = unit_point;
			return (true);
		}
	}
	return (false);
}
