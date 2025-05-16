/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:03:22 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/16 17:43:21 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_grid_map(t_data *data)
{
	int temp_map[4][4] =
	{
		{0, 1, 1, 1},
		{1, 0, 0, 1},
		{1, 0, 'P', 1},
		{0, 1, 1, 1}
	};
	ft_memcpy(data->grid_map, temp_map, sizeof(temp_map));
}

void	init_unit_map(t_data *data)
{
	int	i;
	int	j;

	data->unit_map = malloc(sizeof(data->grid_map) * 4);
	// null check
	i = 0;
	j = 0;
	while (i < MAPX)
	{
		while (j < MAPY)
		{

			j++;
		}
		i++;
	}
}

void	init_maps(t_data *data)
{
	init_grid_map(data);
	init_unit_map(data);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	(void)argc;
	(void)argv;
	// parser(data)
	// init_data
	mlx_t *temp = mlx_init(1080, 1000, "HAHAHAHHA\n\nn\\n\n\n\n\\nn\n", 1);
	//init(&data);
	if(!temp)
		return (0);
	mlx_terminate(temp);
	return (0);
}
