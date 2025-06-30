/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:31:44 by ablodorn          #+#    #+#             */
/*   Updated: 2025/06/30 16:34:55 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	set_coordinates(int **coordinates, int player_x, int player_y)
{
	(*coordinates) = malloc(2 * sizeof(int));
	if (!(*coordinates))
		return (0);
	(*coordinates)[0] = player_y / BLOCK_SIZE;
	(*coordinates)[1] = player_x / BLOCK_SIZE;
	return (1);
}

int	*check_for_door(char **map, int player_x, int player_y,
		t_data *data)
{
	int		i;
	int		*coordinates;
	double	dir_x;
	double	dir_y;
	double	angle_rad;

	i = 0;
	angle_rad = DEG_TO_RAD(data->player.pov.view_angl);
	dir_x = cos(angle_rad);
	dir_y = -sin(angle_rad);
	while (i < 5)
	{
		player_x += dir_x * 80;
		player_y += dir_y * 80;
		if (ft_strchr(DOORS, map[(player_y / BLOCK_SIZE)][(player_x
					/ BLOCK_SIZE)]))
		{
			if (!set_coordinates(&coordinates, player_x, player_y))
				return (NULL);
			return (coordinates);
		}
		i++;
	}
	return (NULL);
}

static void	close_door_10(t_door *doors, t_data *data)
{
	if (has_10_seconds_passed(doors->time_opened))
	{
		if (!player_inside_door(data, doors)
			&& !enemy_inside_door(data, doors))
			doors->state = CLOSING;
	}
}

void	update_doors(t_door *doors, t_data *data)
{
	while (doors)
	{
		if (doors->state == CLOSING)
		{
			if (!player_inside_door(data, doors))
			{
				doors->len += doors->move_spd;
				if (doors->len > BLOCK_SIZE)
					doors->state = CLOSED;
			}
		}
		else if (doors->state == OPENING)
		{
			doors->len -= doors->move_spd;
			if (doors->len < 0)
				doors->state = OPEN;
		}
		if (doors->state == OPEN)
			close_door_10(doors, data);
		doors = doors->next;
	}
}
