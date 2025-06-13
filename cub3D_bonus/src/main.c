/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:03:22 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/14 02:22:21 by mlitvino         ###   ########.fr       */
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

void	adjust_image_alpha(mlx_image_t *img, int new_alpha)
{
	uint32_t	*pixels;
	size_t		total_pixels;
	uint32_t	alpha_mask;
	size_t		i;

	alpha_mask = ((uint32_t)new_alpha) << 24;
	total_pixels = img->width * img->height;
	pixels = (uint32_t *)img->pixels;
	i = 0;
	while (i < total_pixels)
	{
		pixels[i] = (pixels[i] & 0x00FFFFFF) | alpha_mask;
		i++;
	}
}

void	update_statues(t_data *data, t_char *player, t_sprite *sprites)
{
	static int	alpha;
	int			step;

	step = 1;
	while (sprites)
	{
		if (sprites->type == STATUE)
		{
			if (sprites->dist < STATUE_MAX_VIS * BLOCK_SIZE)
			{
				sprites->state = STATUE_RED;
				sprites->cur_img = data->mlx_data.textrs_img[STATUE_RED];
			}
			else
			{
				sprites->state = STATUE_GREY;
				sprites->cur_img = data->mlx_data.textrs_img[STATUE_GREY];
			}
		}
		sprites = sprites->next;
	}

	if (player->facing_statue)
	{
		if (alpha >= 255)
		{
			printf("YOU DIED\n");
			sleep(4);
			clean_all(data);
		}
		alpha += step;
		if (alpha > 255)
			alpha = 255;
	}
	else if (alpha > 0)
	{
		alpha -= step;
	}
	if (alpha > 0)
	{
		adjust_image_alpha(data->mlx_data.textrs_img[STATUE_FACE], alpha);
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
	update_statues(data, &data->player, data->sprite_list);

	raycast(data);
	show_fps();
	draw_minimap(data, data->mlx_data.minimap);

	//show_char_pos(data, &data->player);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	(void)argc;
	(void)argv;
	init_data(&data);

	adjust_image_alpha(data.mlx_data.textrs_img[STATUE_FACE], 0);

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
