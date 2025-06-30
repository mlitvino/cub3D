/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:03:22 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/30 13:34:36 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_usage(void)
{
	printf("Usage: ./cub3D <map_file.cub>\n\n");
	printf("Map Legend:\n");
	printf("  %-3s : %s\n", "0", "grass");
	printf("  %-3s : %s\n", "X", "blood grass");
	printf("  %-3s : %s\n", "F", "wood floor");
	printf("  %-3s : %s\n", "f", "stone floor");
	printf("  %-3s : %s\n", "1", "forest");
	printf("  %-3s : %s\n", "2", "rock wall");
	printf("  %-3s : %s\n", "3", "wagon");
	printf("  %-3s : %s\n", "4", "wood wall");
	printf("  %-3s : %s\n", "5", "stone wall");
	printf("  %-3s : %s\n", "R", "stone road");
	printf("  %-3s : %s\n", "D", "wood door");
	printf("  %-3s : %s\n", "s", "stone door");
	printf("  %-3s : %s\n", "M", "metal door");
	printf("  %-3s : %s\n", "A", "ammo pickup");
	printf("  %-3s : %s\n", "N/S/W/E", "player start");
	printf("  %-3s : %s\n", "d", "dead man");
	printf("  %-3s : %s\n", "C", "statue");
	printf("  %-3s : %s\n", "B", "wolf enemy");
	printf("  %-3s : %s\n", "b", "bones");
	printf("  %-3s : %s\n", "T", "evil_tree");
	printf("  %-3s : %s\n", "G", "exit\n");
	exit(EXIT_SUCCESS);
}

int	parsing_file(t_data *data, char **argv, int argc)
{
	if (argc != 2)
		print_usage();
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
	mlx_resize_hook(data.mlx_data.mlx_ptr, &resize_handler, &data);
	mlx_mouse_hook(data.mlx_data.mlx_ptr, &mouse_hook, &data);
	mlx_loop_hook(data.mlx_data.mlx_ptr, render, &data);
	mlx_loop(data.mlx_data.mlx_ptr);
	clean_all(&data, NULL);
	return (0);
}
