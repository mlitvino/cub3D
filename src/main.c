/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:03:22 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/26 13:43:49 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render(void *data_arg)
{
	t_data *data;

	data = (t_data *)data_arg;
	// //show_unit_map(data);

	raycast(data);
	// show_char_pos(data, &data->player);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	(void)argc;
	(void)argv;
	init_data(&data);

	//show_unit_map(&data);
	//show_char_pos(&data, &data.player);

	//raycast(&data);

	// 128
	// data.player.pos.x = 222;
	// data.player.pos.y = 174;
	// data.player.pov.view_angl = 270;

	// raycast(&data);
	// show_char_pos(&data, &data.player);
	//printf("view_angle: %d\n", data.player.pov.view_angl);
	//show_redline(&data);
	//show_unit_map(&data);

	mlx_key_hook(data.mlx_data.mlx_ptr, &key_event_handler, &data);  //Eventhook for movement

	mlx_loop_hook(data.mlx_data.mlx_ptr, render, &data);
	mlx_loop(data.mlx_data.mlx_ptr);
	clean_all(&data);
	return (0);
}
