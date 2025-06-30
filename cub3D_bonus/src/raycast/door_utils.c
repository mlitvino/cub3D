/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:24:46 by ablodorn          #+#    #+#             */
/*   Updated: 2025/06/30 15:53:59 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	enemy_inside_door(t_data *data, t_door *door)
{
	int			enemy_grid_x;
	int			enemy_grid_y;
	t_sprite	*sprite;

	sprite = data->sprite_list;
	while (sprite)
	{
		enemy_grid_x = sprite->pos.x / BLOCK_SIZE;
		enemy_grid_y = sprite->pos.y / BLOCK_SIZE;
		if (door->grid_y == enemy_grid_y && door->grid_x == enemy_grid_x)
			return (1);
		sprite = sprite->next;
	}
	return (0);
}

int	player_inside_door(t_data *data, t_door *door)
{
	int	player_grid_x;
	int	player_grid_y;

	player_grid_x = data->player.pos.x / BLOCK_SIZE;
	player_grid_y = data->player.pos.y / BLOCK_SIZE;
	if (door->grid_y == player_grid_y && door->grid_x == player_grid_x)
		return (1);
	else
		return (0);
}

int	has_10_seconds_passed(struct timeval start)
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
		microseconds += 100000;
	}
	return (seconds >= 5);
}

struct timeval	get_current_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now);
}
