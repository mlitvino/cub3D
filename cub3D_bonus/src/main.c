/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:03:22 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/05 19:19:24 by mlitvino         ###   ########.fr       */
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


	//jump_baby(&data->player);
	t_door *door = data->door_list;
	open_close(door);
	update_doors(door);

	raycast(data);
	// show_char_pos(data, &data->player);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	(void)argc;
	(void)argv;
	init_data(&data);

	ft_bzero(&data.keys, sizeof(t_keys));
	//show_unit_map(&data);
	show_char_pos(&data, &data.player);
	//show_doors(data.door_list);


	ft_printf("spr x %d, spr y %d\n", data.sprite_list->pos.x, data.sprite_list->pos.y);

	//raycast(&data);

	mlx_key_hook(data.mlx_data.mlx_ptr, &key_event_handler, &data);  //Eventhook for movement

	mlx_loop_hook(data.mlx_data.mlx_ptr, render, &data);
	mlx_loop(data.mlx_data.mlx_ptr);
	clean_all(&data);
	return (0);
}
