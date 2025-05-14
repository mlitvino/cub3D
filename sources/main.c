/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:03:22 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/14 17:25:35 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init(t_data *data)
{
	int map[4][4] =
	{
		{0, 0, 0, 0},
		{0, 1, 1, 1},
		{0, 1, 'P', 1},
		{0, 1, 1, 1}
	};
	ft_memcpy(data->map, map, sizeof(map));
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
	mlx_loop(temp);
	mlx_terminate(temp);
	return (0);
}
