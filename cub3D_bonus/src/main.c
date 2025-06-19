/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:03:22 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/19 12:24:16 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>
#include <sys/time.h>

static void update_bobbing(t_char *player, double delta_time) 
{	
    if (player->is_moving) 
	{
        player->bobbing_time += delta_time * 10.0; // Tune the speed of bobbing
        player->height = 2 + (-sin(player->bobbing_time)) * 0.2;
    } 
	else 
	{
        if (fabs(player->height - player->height) > 0.1)
            player->height = player->height * 0.9 + player->height * 0.1;
        else 
		{
            player->height = 2;
            player->bobbing_time = 0;
        }
    }
}

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

/*void	open_close(t_door *doors)
{
	while (doors)
	{
		if (doors->state == CLOSED)
			doors->state = OPENING;
		if (doors->state == OPEN)
			doors->state = CLOSING;
		doors = doors->next;
	}
}*/

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

long get_time_in_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void	render(void *data_arg)
{
	t_data *data;
	static long previous_time = 0;
	long current_time;
    double delta_time;

	data = (t_data *)data_arg;
	// //show_unit_map(data);
	current_time = get_time_in_ms();
	delta_time = (current_time - previous_time) / 1000.0;
    previous_time = current_time;
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

	update_bobbing(&data->player, delta_time);

	t_door *door = data->door_list;
	//open_close(door);
	update_doors(door, data);
	update_statues(data, &data->player, data->sprite_list);

	raycast(data);
	show_fps();
	draw_minimap(data, data->mlx_data.minimap);
	draw_aim_cross(data->mlx_data.scr_img);

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
