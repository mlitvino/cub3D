/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:58:53 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/01 14:58:54 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_angle(int *count, t_data *data, char angle)
{
	(*count)++;
	if (angle == 'N')
		data->player.pov.view_angl = 90;
	if (angle == 'S')
		data->player.pov.view_angl = 270;
	if (angle == 'W')
		data->player.pov.view_angl = 180;
	if (angle == 'E')
		data->player.pov.view_angl = 0;
}

static void	set_pos(t_data *data, int j, int i)
{
	data->player.pos.x = (j * BLOCK_SIZE) + BLOCK_SIZE / 2;
	data->player.pos.y = (i * BLOCK_SIZE) + BLOCK_SIZE / 2;
}

static int	valid_player_count(char **map, t_data *data)
{
	int	player_count;
	int	i;
	int	j;

	player_count = 0;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				set_angle(&player_count, data, map[i][j]);
				set_pos(data, j, i);
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (0);
	else
		return (1);
}

static int	valid_characters(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr("01NSWED ", map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	valid_map(t_data *data)
{
	char	*msg;

	data->grid_map = pad_map(data->work_map, data->map_h, data);
	if (!data->grid_map)
		return (0);
	if (!valid_player_count(data->work_map, data))
		return (error_free_return("Error\nInvalid player count\n", data));
	if (!valid_characters(data->work_map))
	{
		msg = "Error\nInvalid character found inside the map\n";
		return (error_free_return(msg, data));
	}
	if (!check_map_borders(data->work_map, data->map_h))
	{
		msg = "Error\nMap not surrounded by walls and/or invalid space found\n";
		return (error_free_return(msg, data));
	}
	if (!is_valid_surrounding(data->grid_map, data))
	{
		msg = "Error\nMap not surrounded by walls and/or invalid space found\n";
		return (error_free_return(msg, data));
	}
	free_map(data->work_map, -1);
	return (1);
}
