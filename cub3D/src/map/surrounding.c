/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surrounding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:59:07 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/01 14:59:08 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == 'D');
}

static int	is_allowed_adjacent(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == 'D');
}

static int	check_neighbor(char **map, int n_row, int n_col, t_data *data)
{
	char	neighbor;

	if (n_row >= 0 && n_row < data->map_h
		&& n_col >= 0 && n_col < data->map_w)
	{
		neighbor = map[n_row][n_col];
		if (!is_allowed_adjacent(neighbor))
			return (0);
	}
	else
		return (0);
	return (1);
}

static int	check_neighbors(char **map, int row, int col, t_data *data)
{
	int	delta_row;
	int	delta_col;
	int	n_row;
	int	n_col;

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
				if (!check_neighbor(map, n_row, n_col, data))
					return (0);
			}
			delta_col++;
		}
		delta_row++;
	}
	return (1);
}

int	is_valid_surrounding(char **map, t_data *data)
{
	int		row;
	int		col;
	char	current;

	row = 0;
	while (row < data->map_h)
	{
		col = 0;
		while (col < data->map_w)
		{
			current = map[row][col];
			if (is_walkable(current))
			{
				if (!check_neighbors(map, row, col, data))
					return (0);
			}
			col++;
		}
		row++;
	}
	return (1);
}
