/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:14:16 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/01 17:42:27 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	set_angle_position(char **map, t_data *data, int i, int j)
{
	set_angle(map[i][j], data);
	data->player.pos.y = i * BLOCK_SIZE + (BLOCK_SIZE / 2);
	data->player.pos.x = j * BLOCK_SIZE + (BLOCK_SIZE / 2);
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
				player_count++;
				set_angle_position(map, data, i, j);
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
			if (!ft_strchr(VALID_CHARS, map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	fill_padded_map(int height, t_data *data, char **padded_map, char **map)
{
	int	i;
	int	j;
	int	line_len;

	i = 0;
	while (i < height)
	{
		line_len = ft_strlen(map[i]);
		padded_map[i] = malloc(sizeof(char) * (data->map_w + 1));
		if (!padded_map[i])
			return (perror_free_map(padded_map));
		j = 0;
		while (j < line_len)
		{
			padded_map[i][j] = map[i][j];
			j++;
		}
		while (j < data->map_w)
			padded_map[i][j++] = 'P';
		padded_map[i][data->map_w] = '\0';
		i++;
	}
	padded_map[height] = NULL;
	return (1);
}

int	valid_map(t_data *data)
{
	char	*m;

	data->grid_map = pad_map(data->work_map, data->map_h, data);
	if (!data->grid_map)
		return (0);
	if (!valid_player_count(data->work_map, data))
		return (error_free_return("Error\nInvalid player count\n", data));
	if (!valid_characters(data->work_map))
		return (error_free_return("Error\nInvalid character found inside\n",
				data));
	if (!check_map_borders(data->work_map, data->map_h))
	{
		m = "Error\nMap not surrounded by walls and/or invalid space found\n";
		return (error_free_return(m, data));
	}
	if (!is_valid_surrounding(data))
	{
		m = "Error\nMap not surrounded by walls and/or invalid space found\n";
		return (error_free_return(m, data));
	}
	if (!check_doors(data->work_map))
		return (error_free_return("Error\nInvalid door detected\n", data));
	free_map(data->work_map, -1);
	return (1);
}
