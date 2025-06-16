/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:03:22 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/11 15:57:14 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	jump_baby(t_char *player)
{
	static int shake_sum = 0;
	static int shake_right = 0;
	int	shake_step = player->hitbox_radius / 8;
	static int jump_up = 0;
	double	jump_step = 0.05;

	if (jump_up == true)
	{
		player->height += jump_step;
		if (player->height > 2)
			jump_up = 0;
	}
	else
	{
		player->height -= jump_step;
		if (player->height < 1.5)
			jump_up = 1;
	}

	if (shake_right == 1)
	{
		player->pos.x += shake_step;
		shake_sum += shake_step;
		if (shake_sum > player->hitbox_radius / 2)
			shake_right = 0;
	}
	else
	{
		player->pos.x -= shake_step;
		shake_sum -= shake_step;
		if (shake_sum < player->hitbox_radius / 8)
			shake_right = 1;
	}

}

void	open_close(t_door *doors)
{
	while (doors)
	{
		if (doors->state == CLOSED)
			doors->state = OPENING;
		if (doors->state == OPEN)
			doors->state = CLOSING;
		doors = doors->next;
	}
}

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
	handle_mouse_rotation(data);

	//jump_baby(&data->player);

	t_door *door = data->door_list;
	//open_close(door);
	update_doors(door);

	raycast(data);
	show_fps();
	//draw_minimap(data, data->mlx_data.minimap, data->unit_map, data->player.pos);

	//show_char_pos(data, &data->player);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if(argc != 2)
	{
		printf("Usage: ./cub3D 'file'\n");
		return (1);
	}
	init_null(&data);
	data.map_data = read_file(argv[1], &data);
	if (!data.map_data)
		return (1);
	if (!is_valid_data(data.map_data, &data, data.line_count))
	{
		free_colours_textures_strings(&data);
		free_map(data.map_data, -1);
		return (1);
	}
	free_map(data.map_data, -1);
	if (!valid_map(&data))
	{
		free_colours_textures_strings(&data);
		free_map(data.work_map, -1);
		return (1);
	}
	// int i = 0;
	// while(data.grid_map[i])
	// 	printf("%s\n", data.grid_map[i++]);
	// printf("x %d y %d\n", data.map_h, data.map_w);
	// return (0);
	init_data(&data);
	ft_bzero(&data.keys, sizeof(t_keys));
	//show_unit_map(&data);
	show_char_pos(&data, &data.player);
	//show_doors(data.door_list);

	//raycast(&data);

	mlx_key_hook(data.mlx_data.mlx_ptr, &key_event_handler, &data);  //Eventhook for movement
	mlx_loop_hook(data.mlx_data.mlx_ptr, render, &data);
	mlx_loop(data.mlx_data.mlx_ptr);
	clean_all(&data);
	return (0);
}
