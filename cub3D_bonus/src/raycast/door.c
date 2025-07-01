/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:41:42 by mlitvino          #+#    #+#             */
/*   Updated: 2025/07/01 14:57:45 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_door	*find_door(t_door *doors, int unit_x, int unit_y)
{
	while (doors)
	{
		if (doors->grid_x == unit_x / BLOCK_SIZE
			&& doors->grid_y == unit_y / BLOCK_SIZE)
		{
			return (doors);
		}
		doors = doors->next;
	}
	return (NULL);
}

t_door	*create_door(t_data *data, t_door **door_list, int grid_x, int grid_y)
{
	t_door	*new_door;
	t_door	*temp;

	new_door = malloc(sizeof(t_door));
	if (!new_door)
		return (NULL);
	new_door->type = data->grid_map[grid_y][grid_x];
	new_door->state = CLOSED;
	new_door->len = BLOCK_SIZE;
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

static void door_sound_and_state(t_data *data, t_door *door)
{
	if (door->type == DOOR)
		PlaySound(data->sound[S_DOOR]);
	else if (door->type == MET_DOOR)
		PlaySound(data->sound[S_MET_DOOR]);
	else if (door->type == STONE_DOOR)
		PlaySound(data->sound[S_STONE_DOOR]);
	if (door->state == CLOSED)
	{
		door->state = OPENING;
		door->time_opened = get_current_time();
	}
	else if (door->state == OPEN && !player_inside_door(data, door)
		&& !enemy_inside_door(data, door))
		door->state = CLOSING;
}

void	open_close_door(t_data *data)
{
	int		*coordinates;
	int		door_x;
	int		door_y;
	t_door	*door;

	coordinates = check_for_door(data->grid_map, data->player.pos.x,
			data->player.pos.y, data);
	if (coordinates)
	{
		door_x = coordinates[1];
		door_y = coordinates[0];
		free(coordinates);
		door = find_door(data->door_list, door_x * BLOCK_SIZE, door_y
				* BLOCK_SIZE);
		if (door)
			door_sound_and_state(data, door);
	}
}
