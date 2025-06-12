/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:03:22 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/11 13:46:50 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#include <stdio.h>
#include <sys/time.h>

void show_fps(void)
{
    static struct timeval last = {0, 0};
    static int frames = 0;
    struct timeval now;
    double elapsed;

    gettimeofday(&now, NULL);

    // Initialize last on first call
    if (last.tv_sec == 0 && last.tv_usec == 0)
    {
        last = now;
        return;
    }

    frames++;
    elapsed = (now.tv_sec - last.tv_sec) + (now.tv_usec - last.tv_usec) / 1000000.0;

    if (elapsed >= 1.0)
    {
        printf("FPS: %d\n", frames);
        frames = 0;
        last = now;
    }
}

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
	//show_fps();
	// show_char_pos(data, &data->player);
}

int	parsing_file(t_data *data, char **argv, int argc)
{
	if(argc != 2)
	{
		printf("Usage: ./cub3D 'file'\n");
		return (0);
	}
	init_null(data);
	data->map_data = read_file(argv[1], data);
	if (!data->map_data)
		return (0);
	if (!is_valid_data(data->map_data, data, data->line_count))
	{
		free_colours_textures_strings(data);
		free_map(data->map_data, -1);
		return (0);
	}
	free_map(data->map_data, -1);
	if (!valid_map(data))
	{
		free_colours_textures_strings(data);
		free_map(data->work_map, -1);
		return (0);
	}
	//this needs to be freed later: free_colours_textures_strings() call and grid_map.
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (!parsing_file(&data, argv, argc))
		return (1);
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
	
	mlx_key_hook(data.mlx_data.mlx_ptr, &key_event_handler, &data);
	mlx_loop_hook(data.mlx_data.mlx_ptr, render, &data);
	mlx_loop(data.mlx_data.mlx_ptr);
	clean_all(&data);
	return (0);
}
