/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:41:42 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/02 13:23:36 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update_doors(t_door *doors)
{
	while (doors)
	{
		if (doors->state == CLOSING)
		{
			doors->len += doors->move_spd;
			if (doors->len > BLOCK_SIZE)
				doors->state = CLOSED;
		}
		else if (doors->state == OPENING)
		{
			doors->len -= doors->move_spd;
			if (doors->len < 0)
				doors->state = OPEN;
		}
		doors = doors->next;
	}
}

t_door	*find_door(t_door *doors, int unit_x, int unit_y)
{
	while (doors)
	{
		if (doors->grid_x == unit_x / BLOCK_SIZE)
			if (doors->grid_y == unit_y / BLOCK_SIZE)
				return (doors);
		doors = doors->next;
	}
	return (NULL);
}

t_door	*create_door(t_door **door_list, int grid_x, int grid_y)
{
	t_door	*new_door;
	t_door	*temp;

	new_door = malloc(sizeof(t_door));
	if (!new_door)
		return (NULL);
	new_door->state = CLOSED;
	new_door->len = BLOCK_SIZE / 2;
	new_door->grid_x = grid_x;
	new_door->grid_y = grid_y;
	new_door->next = NULL;
	new_door->move_spd = BLOCK_SIZE / 64;
	temp = *door_list;
	while (temp && temp->next)
		temp = temp->next;
	if (!temp)
		*door_list = new_door;
	else if (!temp->next)
		temp->next = new_door;
	return (new_door);
}
