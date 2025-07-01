/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surrounding_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:24:28 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/01 17:42:27 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	check_single_neighbor(char **map, int n_row,
		int n_col, t_data *data)
{
	char	neighbor;

	if (n_row >= 0 && n_row < data->map_h && n_col >= 0 && n_col < data->map_w)
	{
		neighbor = map[n_row][n_col];
		if (neighbor == ' ' || neighbor == 'P')
			return (0);
	}
	else
		return (0);
	return (1);
}

static int	check_neighbors(t_data *data, int row, int col)
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
				if (!check_single_neighbor(data->grid_map, n_row, n_col, data))
					return (0);
			}
			delta_col++;
		}
		delta_row++;
	}
	return (1);
}

int	is_valid_surrounding(t_data *data)
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
			current = data->grid_map[row][col];
			if (!ft_strchr(WALLS, current) && ft_strchr(VALID_CHARS, current)
				&& current != ' ')
			{
				if (!check_neighbors(data, row, col))
					return (0);
			}
			col++;
		}
		row++;
	}
	return (1);
}
