/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:03:22 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/03 16:02:18 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render(void *data_arg)
{
	t_data *data;

	data = (t_data *)data_arg;
	// //show_unit_map(data);
	if (data->keys.w)
        move_player(&data->player, 0);
    if (data->keys.a)
        move_player(&data->player, 90);
	if (data->keys.s)
        move_player(&data->player, 180);
    if (data->keys.d)
        move_player(&data->player, -90);
    if (data->keys.left)
        rotate_player_right(&data->player);
    if (data->keys.right)
        rotate_player_left(&data->player);
	raycast(data);
	// show_char_pos(data, &data->player);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if(argc != 2)
	{
		printf("Usage: ./cub3D 'file'\n");
		return (1);
	}
	init_null(&data);
	//init_data(&data);
	data.map_data = read_file(argv[1], &data);
	if (!data.map_data)
		return (1);
	if (!is_valid_data(data.map_data, &data, data.line_count))
	{
		free_colours_textures_strings(&data);
		free_map(data.map_data, -1);
		return (1);
	}
	free_map(data.map_data, -1); //not needed anymore
	if (!valid_map(&data))
	{
		free_colours_textures_strings(&data);
		free_map(data.work_map, -1);
		return (1);
	}
	if (!valid_wall_paths(&data))
	{
		free_colours_textures_strings(&data);
		free_map(data.grid_map, -1);
		return (1);
	}
	init_data(&data);

	ft_bzero(&data.keys, sizeof(t_keys));
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
