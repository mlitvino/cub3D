/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:03:22 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/23 12:50:59 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parsing_file(t_data *data, char **argv, int argc)
{
	if (argc != 2)
	{
		printf("Usage: ./cub3D 'file'\n");
		return (0);
	}
	data->map_data = read_file(argv[1], data);
	if (!data->map_data)
		return (0);
	if (!is_valid_data(data->map_data, data, data->line_count))
	{
		free_map(data->map_data, -1);
		return (0);
	}
	free_map(data->map_data, -1);
	if (!valid_map(data))
	{
		free_map(data->work_map, -1);
		return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (!parsing_file(&data, argv, argc))
		return (1);
	init_data(&data);
	mlx_key_hook(data.mlx_data.mlx_ptr, &key_event_handler, &data);
	mlx_loop_hook(data.mlx_data.mlx_ptr, render, &data);
	mlx_loop(data.mlx_data.mlx_ptr);
	clean_all(&data, NULL);
	return (0);
}
