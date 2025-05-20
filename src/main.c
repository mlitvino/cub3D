/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:03:22 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/21 00:25:45 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render(void *data_arg)
{
	t_data *data;

	data = (t_data *)data_arg;
	show_unit_map(data);
	show_char_pos(data, &data->player);
	//move
	//hook
}

int	main(int argc, char *argv[])
{
	t_data	data;

	(void)argc;
	(void)argv;
	// parser(data)
	init_data(&data);

	show_unit_map(&data);
	show_char_pos(&data, &data.player);

	raycast(&data);

	//mlx_loop_hook(data.mlx_data.mlx_ptr, render, &data);
	//mlx_loop(data.mlx_data.mlx_ptr);
	clean_all(&data);
	return (0);
}
