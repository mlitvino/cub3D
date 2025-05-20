/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:11:45 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/20 18:09:56 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_grid_map(t_data *data)
{
	char temp_map[TEST_MAPY][TEST_MAPX] =
	{
		{0, 1, 1, 1},
		{1, 1, 1, 1},
		{1, 0, 0, 1},
		{PLAYER, 0, 1, 1}
	};

	ft_memcpy(data->grid_map, temp_map, sizeof(temp_map));
}

void	init_unit_map(t_data *data)
{
	int	y;
	int	x;

	data->unit_map = ft_calloc(data->map_h * BLOCK_SIZE, sizeof(char *));
	// null check
	y = 0;
	while (y < data->map_h * BLOCK_SIZE)
	{
		data->unit_map[y] = ft_calloc(data->map_w * BLOCK_SIZE, sizeof(char));
		x = 0;
		while (x < data->map_w)
		{
			if (data->grid_map[y / BLOCK_SIZE][x] != PLAYER)
				ft_memset(&data->unit_map[y][x * BLOCK_SIZE],
					data->grid_map[y / BLOCK_SIZE][x], BLOCK_SIZE);
			x++;
		}
		y++;
	}
}

void	init_maps(t_data *data)
{
	init_grid_map(data);
	data->map_h = TEST_MAPY;
	data->map_w = TEST_MAPX;
	init_unit_map(data);
}

void	init_player(t_data *data)
{
	int		pos_x;
	int		pos_y;
	t_char *player;
	int		hitbox;

	player = &data->player;

	player->data = data;
	player->hitbox_radius = BLOCK_SIZE / 4;
	player->pov.fov = FOV;
	player->pov.view_angl = 15;
	player->height = BLOCK_SIZE / 2;

	player->move_spd = 1;
	player->turn_spd = 1;

	hitbox = player->hitbox_radius;

	for (int y = 0; y < TEST_MAPX; y++)
	{
		for(int x = 0; x < TEST_MAPY; x++)
		{
			if (data->grid_map[y][x] == PLAYER)
			{
				pos_y = (y * BLOCK_SIZE) + BLOCK_SIZE / 2;
				pos_x = (x * BLOCK_SIZE) + BLOCK_SIZE / 2;
			}
		}
	}

	player->pos.x = pos_x;
	player->pos.y = pos_y;

	data->unit_map[pos_y][pos_x] = PLAYER;

	for (int y = pos_y - hitbox; y <= pos_y + hitbox; y++)
		for (int x = pos_x - hitbox; x <= pos_x + hitbox; x++)
			data->unit_map[y][x] = PLAYER;
}

void	init_mlx(t_data *data)
{
	t_mlx	mlx_data;

	//mlx_set_setting(MLX_STRETCH_IMAGE, true); // resize scr_img with resizing win
	mlx_set_setting(MLX_HEADLESS, true); // disable_win
	mlx_data.mlx_ptr = mlx_init(WIN_W + 100, WIN_H + 100, "cub3D", true);
	mlx_data.scr_img = mlx_new_image(mlx_data.mlx_ptr, WIN_W, WIN_H);

	int res1 = mlx_image_to_window(mlx_data.mlx_ptr, mlx_data.scr_img, 0, 0);

	for (int x = 0; x < WIN_W; x++)
		for(int y = 0; y < WIN_H; y++)
			mlx_put_pixel(mlx_data.scr_img, x, y, 0x000000FF); // BLACK

	mlx_data.textrs[NORTH] = mlx_load_png("./textures/north.png"); // change to path to file
	mlx_data.textrs[EAST] = mlx_load_png("./textures/east.png");
	mlx_data.textrs[WEST] = mlx_load_png("./textures/west.png");
	mlx_data.textrs[SOUTH] = mlx_load_png("./textures/south.png");

	mlx_data.textrs_img[NORTH] = mlx_texture_to_image(mlx_data.mlx_ptr, mlx_data.textrs[NORTH]);
	mlx_resize_image(mlx_data.textrs_img[NORTH], BLOCK_SIZE * 100, BLOCK_SIZE * 100);

	mlx_data.textrs_img[EAST] = mlx_texture_to_image(mlx_data.mlx_ptr, mlx_data.textrs[EAST]);
	mlx_resize_image(mlx_data.textrs_img[EAST], BLOCK_SIZE * 100, BLOCK_SIZE * 100);

	mlx_data.textrs_img[WEST] = mlx_texture_to_image(mlx_data.mlx_ptr, mlx_data.textrs[WEST]);
	mlx_resize_image(mlx_data.textrs_img[WEST], BLOCK_SIZE * 100, BLOCK_SIZE * 100);

	mlx_data.textrs_img[SOUTH] = mlx_texture_to_image(mlx_data.mlx_ptr, mlx_data.textrs[SOUTH]);
	mlx_resize_image(mlx_data.textrs_img[SOUTH], BLOCK_SIZE * 100, BLOCK_SIZE * 100);


	mlx_image_to_window(mlx_data.mlx_ptr, mlx_data.textrs_img[EAST], 50, 50);

	data->mlx_data = mlx_data;
}

void	init_data(t_data *data)
{
	init_maps(data);
	init_player(data);
	init_mlx(data);

	data->plane.width = WIN_W; // TEST
	data->plane.height = WIN_H; // TEST


	data->plane.center.x = WIN_W / 2;
	data->plane.center.x = WIN_H / 2;
	data->plane.dist = (WIN_W / 2) / (int)tan(FOV / 2);

	data->rays_count = WIN_W;
	data->rays_angle = FOV / (double)data->rays_count;// double?
	printf("RAY_ANGLE %f\n", data->rays_angle); //del
}
