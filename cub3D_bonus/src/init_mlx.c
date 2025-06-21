/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:55:28 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/22 02:21:12 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	resize_image(mlx_image_t *img, int img_i)
{
	if (img_i == SKY_TEX)
		return (mlx_resize_image(img, SKY_W, SKY_H));
	else if (img_i == CROSSBOW1 || img_i == CROSSBOW2 || img_i == STATUE_FACE)
		return (mlx_resize_image(img, WIN_W, WIN_H));
	else
		return (mlx_resize_image(img, BLOCK_SIZE, BLOCK_SIZE));
}

void	*init_tex(t_mlx *mlx_data, mlx_texture_t **tex)
{
	// mlx_image_t	**tex_img;
	// int			i;

	// tex_img = mlx_data->textrs_img;
	// i = 0;
	// while (i < MAX_TEX)
	// {
	// 	tex[i] = mlx_load_png(mlx_data->tex_path[i]);
	// 	if (!tex[i])
	// 		return (NULL);
	// 	tex_img[i] = mlx_texture_to_image(mlx_data->mlx_ptr, tex[i]);
	// 	if (!tex_img[i])
	// 		return (NULL);
	// 	if (!resize_image(tex_img[i], i))
	// 		return (NULL);
	// 	i++;
	// }

	mlx_data->textrs[NORTH] = mlx_load_png("./textures/forest.png");
	mlx_data->textrs_img[NORTH] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[NORTH]);
	mlx_resize_image(mlx_data->textrs_img[NORTH], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data->textrs[EAST] = mlx_load_png("./textures/forest.png");
	mlx_data->textrs_img[EAST] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[EAST]);
	mlx_resize_image(mlx_data->textrs_img[EAST], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data->textrs[WEST] = mlx_load_png("./textures/forest.png");
	mlx_data->textrs_img[WEST] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[WEST]);
	mlx_resize_image(mlx_data->textrs_img[WEST], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data->textrs[SOUTH] = mlx_load_png("./textures/forest.png");
	mlx_data->textrs_img[SOUTH] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[SOUTH]);
	mlx_resize_image(mlx_data->textrs_img[SOUTH], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data->textrs[DOOR_TEX] = mlx_load_png("./textures/wood_door.png");
	mlx_data->textrs_img[DOOR_TEX] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[DOOR_TEX]);
	mlx_resize_image(mlx_data->textrs_img[DOOR_TEX], BLOCK_SIZE, BLOCK_SIZE);


	mlx_data->textrs[FLOOR_TEX] = mlx_load_png("./textures/wood_floor.png");
	mlx_data->textrs_img[FLOOR_TEX] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[FLOOR_TEX]);
	mlx_resize_image(mlx_data->textrs_img[FLOOR_TEX], BLOCK_SIZE, BLOCK_SIZE);


	mlx_data->textrs[GROUND_TEX] = mlx_load_png("./textures/grass.png");
	mlx_data->textrs_img[GROUND_TEX] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[GROUND_TEX]);
	mlx_resize_image(mlx_data->textrs_img[GROUND_TEX], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data->textrs[WOLF_STAY] = mlx_load_png("./textures/wolf/wolf_stay.png");
	mlx_data->textrs_img[WOLF_STAY] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[WOLF_STAY]);
	mlx_resize_image(mlx_data->textrs_img[WOLF_STAY], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data->textrs[WOLF_WALK1] = mlx_load_png("./textures/wolf/wolf_walk1.png");
	mlx_data->textrs_img[WOLF_WALK1] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[WOLF_WALK1]);
	mlx_resize_image(mlx_data->textrs_img[WOLF_WALK1], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data->textrs[WOLF_WALK2] = mlx_load_png("./textures/wolf/wolf_walk2.png");
	mlx_data->textrs_img[WOLF_WALK2] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[WOLF_WALK2]);
	mlx_resize_image(mlx_data->textrs_img[WOLF_WALK2], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data->textrs[WOLF_ATTCK] = mlx_load_png("./textures/wolf/wolf_attck.png");
	mlx_data->textrs_img[WOLF_ATTCK] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[WOLF_ATTCK]);
	mlx_resize_image(mlx_data->textrs_img[WOLF_ATTCK], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data->textrs[WOLF_DEAD] = mlx_load_png("./textures/wolf/wolf_dead.png");
	mlx_data->textrs_img[WOLF_DEAD] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[WOLF_DEAD]);
	mlx_resize_image(mlx_data->textrs_img[WOLF_DEAD], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data->textrs[STATUE_GREY] = mlx_load_png("./textures/statue/statue_grey.png");
	mlx_data->textrs_img[STATUE_GREY] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[STATUE_GREY]);
	mlx_resize_image(mlx_data->textrs_img[STATUE_GREY], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data->textrs[STATUE_RED] = mlx_load_png("./textures/statue/statue_red.png");
	mlx_data->textrs_img[STATUE_RED] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[STATUE_RED]);
	mlx_resize_image(mlx_data->textrs_img[STATUE_RED], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data->textrs[CEIL_TEX] = mlx_load_png("./textures/wood_ceil.png");
	mlx_data->textrs_img[CEIL_TEX] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[CEIL_TEX]);
	mlx_resize_image(mlx_data->textrs_img[CEIL_TEX], BLOCK_SIZE, BLOCK_SIZE);

	mlx_data->textrs[STATUE_FACE] = mlx_load_png("./textures/statue/statue_face.png");
	mlx_data->textrs_img[STATUE_FACE] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[STATUE_FACE]);
	mlx_resize_image(mlx_data->textrs_img[STATUE_FACE], mlx_data->scr_img->width, mlx_data->scr_img->height);

	mlx_data->textrs[CROSSBOW1] = mlx_load_png("./textures/crossbow1.png");
	mlx_data->textrs_img[CROSSBOW1] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[CROSSBOW1]);
	mlx_resize_image(mlx_data->textrs_img[CROSSBOW1], mlx_data->scr_img->width, mlx_data->scr_img->height);

	mlx_data->textrs[CROSSBOW2] = mlx_load_png("./textures/crossbow2.png");
	mlx_data->textrs_img[CROSSBOW2] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[CROSSBOW2]);
	mlx_resize_image(mlx_data->textrs_img[CROSSBOW2], mlx_data->scr_img->width, mlx_data->scr_img->height);

	mlx_data->textrs[SKY_TEX] = mlx_load_png("./textures/sky.png");
	mlx_data->textrs_img[SKY_TEX] = mlx_texture_to_image(mlx_data->mlx_ptr, mlx_data->textrs[SKY_TEX]);
	mlx_resize_image(mlx_data->textrs_img[SKY_TEX], 1440, 5000);

	return (*tex);
}

void	put_img_to_win(t_data *data, mlx_image_t *img)
{
	t_mlx	*mlx_data;

	mlx_data = &data->mlx_data;
	if (mlx_image_to_window(data->mlx_data.mlx_ptr, img, 0, 0) < 0)
		clean_all(data, NULL); // add err message
	if (img == mlx_data->minimap)
		mlx_set_instance_depth(&img->instances[0], 1);
	else if (img == mlx_data->textrs_img[CROSSBOW1]
		|| img == mlx_data->textrs_img[CROSSBOW2])
		mlx_set_instance_depth(&img->instances[0], 2);
	else if (img == mlx_data->textrs_img[STATUE_FACE])
		mlx_set_instance_depth(&img->instances[0], 3);
	else if (img != mlx_data->scr_img)
	{
		mlx_set_instance_depth(&img->instances[0], 4);
		img->enabled = 0;
	}
}

bool	put_images_to_window(t_data *data, t_mlx *mlx_data)
{
	mlx_data->minimap = mlx_new_image(mlx_data->mlx_ptr, MINIMAP_W, MINIMAP_H);
	if (!mlx_data->minimap)
		clean_all(data, "mlx: minimap");
	put_img_to_win(data, mlx_data->scr_img);
	put_img_to_win(data, mlx_data->minimap);
	put_img_to_win(data, mlx_data->textrs_img[CROSSBOW1]);
	put_img_to_win(data, mlx_data->textrs_img[CROSSBOW2]);
	put_img_to_win(data, mlx_data->textrs_img[STATUE_FACE]);
	return (true);
}

void	init_mlx(t_data *data)
{
	t_mlx	*mlx_data;

	ft_bzero(&data->mlx_data, sizeof(t_mlx));
	mlx_data = &data->mlx_data;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_data->mlx_ptr = mlx_init(WIN_W, WIN_H, "cub3D", true);
	if (!mlx_data->mlx_ptr)
		clean_all(data, "mlx");
	mlx_data->scr_img = mlx_new_image(mlx_data->mlx_ptr, WIN_W, WIN_H);
	if (!mlx_data->scr_img)
		clean_all(data, "mlx");
	if (!init_tex(mlx_data, mlx_data->textrs))
		clean_all(data, "mlx");
	if (!put_images_to_window(data, &data->mlx_data))
		clean_all(data, "mlx");
	mlx_set_icon(mlx_data->mlx_ptr, mlx_data->textrs[WOLF_STAY]);
}
