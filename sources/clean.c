/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 23:12:04 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/17 23:29:44 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clean_map(t_data *data)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (col < data->map_w * BLOCK_SIZE)
	{
		free(data->unit_map[col]);
		data->unit_map[col] = NULL;
		col++;
	}
	free(data->unit_map);
	data->unit_map = NULL;
}

void	clean_mlx(t_data *data)
{
	mlx_terminate(data->mlx_data.mlx_ptr);
}

void	clean_all(t_data *data)
{
	clean_map(data);
	clean_mlx(data);
}
