/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:41:42 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/21 20:20:07 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static struct timeval	get_current_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now);
}

static int	*check_for_door(char **map, int row, int col)
{
	int	delta_row;
	int	delta_col;
	int	n_row;
	int	n_col;
	int	*coordinates;

	row = row / BLOCK_SIZE;
	col = col / BLOCK_SIZE;
	delta_row = -1;
	while (delta_row <= 1)
	{
		delta_col = -1;
		while (delta_col <= 1)
		{
			if (!(delta_row == 0 && delta_col == 0))
			{
				n_row = row + delta_row;
				n_col = col + delta_col;
				if (map[n_row][n_col] == 'D')
				{
					coordinates = malloc(2 * sizeof(int));
					if (!coordinates)
						return (NULL);
					coordinates[0] = n_row;
					coordinates[1] = n_col;
					return (coordinates);
				}
			}
			delta_col++;
		}
		delta_row++;
	}
	return (NULL);
}

void	open_door(t_data *data)
{
	int		*coordinates;
	int		door_x;
	int		door_y;
	t_door	*door;

	coordinates = check_for_door(data->grid_map, data->player.pos.y,
			data->player.pos.x);
	if (coordinates)
	{
		door_x = coordinates[1];
		door_y = coordinates[0];
		free(coordinates);
		door = find_door(data->door_list, door_x * BLOCK_SIZE, door_y
				* BLOCK_SIZE);
		if (door && data->player.door_facing != 0
			&& data->player.door_facing < BLOCK_SIZE * 3)
		{
			if (door->state == CLOSED)
				if (IsSoundPlaying(data->sound[S_DOOR]) == false)
					PlaySound(data->sound[S_DOOR]);
			door->state = OPENING;
			door->time_opened = get_current_time();
		}
	}
}

static int	has_10_seconds_passed(struct timeval start)
{
	struct timeval	now;
	long			seconds;
	long			microseconds;

	now = get_current_time();
	seconds = now.tv_sec - start.tv_sec;
	microseconds = now.tv_usec - start.tv_usec;
	if (microseconds < 0)
	{
		seconds -= 1;
		microseconds += 1000000;
	}
	return (seconds >= 10);
}

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
		if (doors->state == OPEN)
		{
			if (has_10_seconds_passed(doors->time_opened))
				doors->state = CLOSING;
		}
		doors = doors->next;
	}
}

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

t_door	*create_door(t_door **door_list, int grid_x, int grid_y)
{
	t_door	*new_door;
	t_door	*temp;

	new_door = malloc(sizeof(t_door));
	if (!new_door)
		return (NULL);
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
