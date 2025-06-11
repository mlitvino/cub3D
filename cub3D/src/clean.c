/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 23:12:04 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/28 14:00:26 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clean_map(t_data *data)
{
	int	y;

	y = 0;
	while (y < data->map_h * BLOCK_SIZE)
	{
		free(data->unit_map[y]);
		data->unit_map[y] = NULL;
		y++;
	}
	free(data->unit_map);
	data->unit_map = NULL;
}

void	clean_mlx(t_data *data)
{
	t_mlx	mlx_data;

	mlx_data = data->mlx_data;
	for (int i = 0; i < MAX_TEX; i++)
	{
		mlx_delete_texture(mlx_data.textrs[i]);
		mlx_delete_image(mlx_data.mlx_ptr, mlx_data.textrs_img[i]);
	}
	mlx_terminate(mlx_data.mlx_ptr);
}

void	clean_all(t_data *data)
{
	clean_map(data);
	clean_mlx(data);
	exit(0);
}
