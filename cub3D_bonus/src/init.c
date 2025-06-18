/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:11:45 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/17 16:10:54 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*void	init_grid_map(t_data *data)
{
	//y 8 x 7, change TEST_MAPY, TEST_MAPX
	// char temp_map[TEST_MAPY][TEST_MAPX] =
	// {
	// 	{1, 1, 1, 1, 1, 1, 1},
	// 	{1, 0, 0, PLAYER, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 1},
	// 	{1, 1, 1, DOOR, 1, 1, 1},
	// 	{1, 0, 0, WOLF, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 1},
	// 	{1, 1, 1, 1, 1, 1, 1},
	// };

	// DOOR MAP
	// char temp_map[TEST_MAPY][TEST_MAPX] =
	// {
	// 	{1, 1, 1, 1, 1, 1, 1},
	// 	{1, 0, 1, 0, 0, 1, 1},
	// 	{1, 1, 1, DOOR, 1, 1, 1},
	// 	{1, 0, 1, 0, 0, 1, 1},
	// 	{1, 0, DOOR, PLAYER, 0, DOOR, 1},
	// 	{1, 0, 1, DOOR, 1, 1, 1},
	// 	{1, 0, 1, 0, 1, 0, 1},
	// 	{1, 1, 1, 1, 1, 1, 1},
	// };

	//y 14 x 33, change TEST_MAPY, TEST_MAPX
	char temp_map[TEST_MAPY][TEST_MAPX] = {
		{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,0,1,1,0,0,PLAYER,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,0,1,0,0,0,1,0,0,0,0},
		{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,0,1,0,0,0,1,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,1,0,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,0,0},
		{1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
	};

	ft_memcpy(data->grid_map, temp_map, sizeof(temp_map));
}*/

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
	//init_grid_map(data);
	//data->map_h = TEST_MAPY;
	//data->map_w = TEST_MAPX;
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
	//player->pov.view_angl = 90;
	player->height = 2;

	player->move_spd = BLOCK_SIZE / 24;
	player->turn_spd = 2;

	player->is_moving = 0;
	hitbox = player->hitbox_radius;

	printf("x %d y %d\n", data->map_h, data->map_w);
	for(int y = 0; y < data->map_h; y++)
	{
		for (int x = 0; x < data->map_w; x++)
		{
			if (data->grid_map[y][x] == PLAYER)
			{
				pos_y = (y * BLOCK_SIZE) + BLOCK_SIZE / 2;
				pos_x = (x * BLOCK_SIZE) + BLOCK_SIZE / 2;
			}
			if (data->grid_map[y][x] == DOOR)
			{
				if (create_door(&data->door_list, x, y) == NULL)
					clean_all(data); // IMRPOVE
			}
			if (data->grid_map[y][x] == WOLF)
			{
				if (create_sprite(data, WOLF, x, y) == NULL)
					clean_all(data); // IMRPOVE
			}
			// if (data->grid_map[y][x] == CANDLE)
			// {
			// 	if (create_sprite(&data->door_list, CANDLE, x, y) == NULL)
			// 		clean_all(data); // IMRPOVE
			// }
		}
	}

	player->pos.x = pos_x;
	player->pos.y = pos_y;

	printf("pos x %d, pos y %d\n", pos_x, pos_y);

	data->unit_map[pos_y][pos_x] = PLAYER;

	for (int y = pos_y - hitbox; y <= pos_y + hitbox; y++)
		for (int x = pos_x - hitbox; x <= pos_x + hitbox; x++)
			data->unit_map[y][x] = PLAYER;
}

void	init_mlx(t_data *data)
{
	t_mlx	mlx_data;

	ft_memset(&mlx_data, 0, sizeof(t_mlx));
	mlx_set_setting(MLX_STRETCH_IMAGE, true); // resize scr_img with resizing win
	//mlx_set_setting(MLX_HEADLESS, true); // disable_win
	mlx_data.mlx_ptr = mlx_init(WIN_W, WIN_H, "cub3D", true);
	mlx_data.scr_img = mlx_new_image(mlx_data.mlx_ptr, WIN_W, WIN_H);

	int res1 = mlx_image_to_window(mlx_data.mlx_ptr, mlx_data.scr_img, 0, 0);

	for (int x = 0; x < WIN_W; x++)
		for(int y = 0; y < WIN_H; y++)
			mlx_put_pixel(mlx_data.scr_img, x, y, 0x000000FF); // BLACK


	mlx_data.minimap = mlx_new_image(mlx_data.mlx_ptr, WIN_W / 4, WIN_W / 4);

	int res2 = mlx_image_to_window(mlx_data.mlx_ptr, mlx_data.minimap, 0, 0);

	for (int x = 0; x < mlx_data.minimap->width; x++)
		for(int y = 0; y < mlx_data.minimap->height; y++)
			mlx_put_pixel(mlx_data.minimap, x, y, 0xFF / 2); // BLACK

	mlx_set_instance_depth(&mlx_data.scr_img->instances[res1], 0);
	mlx_set_instance_depth(&mlx_data.minimap->instances[res2], 1);


	mlx_data.textrs[NORTH] = mlx_load_png("./textures/north.png"); // change to path to file
	mlx_data.textrs_img[NORTH] = mlx_texture_to_image(mlx_data.mlx_ptr, mlx_data.textrs[NORTH]);
	mlx_resize_image(mlx_data.textrs_img[NORTH], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data.textrs[EAST] = mlx_load_png("./textures/east.png");
	mlx_data.textrs_img[EAST] = mlx_texture_to_image(mlx_data.mlx_ptr, mlx_data.textrs[EAST]);
	mlx_resize_image(mlx_data.textrs_img[EAST], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data.textrs[WEST] = mlx_load_png("./textures/west.png");
	mlx_data.textrs_img[WEST] = mlx_texture_to_image(mlx_data.mlx_ptr, mlx_data.textrs[WEST]);
	mlx_resize_image(mlx_data.textrs_img[WEST], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data.textrs[SOUTH] = mlx_load_png("./textures/south.png");
	mlx_data.textrs_img[SOUTH] = mlx_texture_to_image(mlx_data.mlx_ptr, mlx_data.textrs[SOUTH]);
	mlx_resize_image(mlx_data.textrs_img[SOUTH], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data.textrs[DOOR_TEX] = mlx_load_png("./textures/door.png");
	mlx_data.textrs_img[DOOR_TEX] = mlx_texture_to_image(mlx_data.mlx_ptr, mlx_data.textrs[DOOR_TEX]);
	mlx_resize_image(mlx_data.textrs_img[DOOR_TEX], BLOCK_SIZE, BLOCK_SIZE);



	mlx_data.textrs[WOLF_STAY] = mlx_load_png("./textures/wolf/wolf_stay.png");
	mlx_data.textrs_img[WOLF_STAY] = mlx_texture_to_image(mlx_data.mlx_ptr, mlx_data.textrs[WOLF_STAY]);
	mlx_resize_image(mlx_data.textrs_img[WOLF_STAY], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data.textrs[WOLF_WALK1] = mlx_load_png("./textures/wolf/wolf_walk1.png");
	mlx_data.textrs_img[WOLF_WALK1] = mlx_texture_to_image(mlx_data.mlx_ptr, mlx_data.textrs[WOLF_WALK1]);
	mlx_resize_image(mlx_data.textrs_img[WOLF_WALK1], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data.textrs[WOLF_WALK2] = mlx_load_png("./textures/wolf/wolf_walk2.png");
	mlx_data.textrs_img[WOLF_WALK2] = mlx_texture_to_image(mlx_data.mlx_ptr, mlx_data.textrs[WOLF_WALK2]);
	mlx_resize_image(mlx_data.textrs_img[WOLF_WALK2], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data.textrs[WOLF_ATTCK] = mlx_load_png("./textures/wolf/wolf_attck.png");
	mlx_data.textrs_img[WOLF_ATTCK] = mlx_texture_to_image(mlx_data.mlx_ptr, mlx_data.textrs[WOLF_ATTCK]);
	mlx_resize_image(mlx_data.textrs_img[WOLF_ATTCK], BLOCK_SIZE, BLOCK_SIZE);

	data->mlx_data = mlx_data;

	//mlx_set_cursor_mode(data->mlx_data.mlx_ptr, MLX_MOUSE_DISABLED); //hides mouse
}

void	init_data(t_data *data)
{
	init_mlx(data);
	init_maps(data);
	init_player(data);

	data->plane.center.x = WIN_W / 2;
	data->plane.center.y = WIN_H / 2;
	data->plane.dist = (WIN_W / 2) / tan(deg_rad(FOV / 2));

	data->rays_count = WIN_W;
	data->rays_angle = FOV / (double)data->rays_count;

	data->flor_rgb.rgbt = 0x545454fc;
	data->ceil_rgb.rgbt = 0xFF;
	// data->flor_rgb.rgbt = 0xFF;
	// data->ceil_rgb.rgbt = 0xFF;
}
