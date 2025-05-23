/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:03:22 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/23 13:32:27 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render(void *data_arg)
{
	t_data *data;

	data = (t_data *)data_arg;
	//show_unit_map(data);
	raycast(&data);
	mlx_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.scr_img, 0, 0);
	sleep(1);
	// show_char_pos(data, &data->player);
	//move
	//hook
}

void	hook(mlx_key_data_t key_data, void *data_param)
{
	t_data *data;

	data = (t_data *)data_param;
	clean_all(data);
}



int	main(int argc, char *argv[])
{
	t_data	data;

	(void)argc;
	(void)argv;
	// parser(data)
	init_data(&data);

	//show_unit_map(&data);
	//show_char_pos(&data, &data.player);

	raycast(&data);
	//mlx_key_hook(data.mlx_data.mlx_ptr, &hook, &data);
	mlx_key_hook(data.mlx_data.mlx_ptr, &key_event_handler, &data);  //Eventhook for movement

	mlx_loop_hook(data.mlx_data.mlx_ptr, render, &data);
	mlx_loop(data.mlx_data.mlx_ptr);
	clean_all(&data);
	return (0);
}
