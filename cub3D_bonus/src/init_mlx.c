/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:55:28 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/25 17:24:55 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static const char	*g_tex_path[MAX_TEX] = {
	[NORTH] = NORTH_PATH,
	[EAST] = EAST_PATH,
	[WEST] = WEST_PATH,
	[SOUTH] = SOUTH_PATH,
	[WAGON_TEX] = WAGON_TEX_PATH,
	[ROCK_TEX] = ROCK_TEX_PATH,
	[WALL_TEX] = WALL_TEX_PATH,
	[DOOR_TEX] = DOOR_TEX_PATH,
	[MET_DOOR_TEX] = MET_DOOR_TEX_PATH,
	[FLOOR_TEX] = FLOOR_TEX_PATH,
	[GROUND_TEX] = GROUND_TEX_PATH,
	[CEILING_TEX] = CEILING_TEX_PATH,
	[SKY_TEX] = SKY_TEX_PATH,
	[DEAD_MAN_TEX] = DEAD_MAN_PATH,
	[WOLF_STAY] = WOLF_STAY_PATH,
	[WOLF_WALK1] = WOLF_WALK1_PATH,
	[WOLF_WALK2] = WOLF_WALK2_PATH,
	[WOLF_ATTCK] = WOLF_ATTCK_PATH,
	[WOLF_DEAD] = WOLF_DEAD_PATH,
	[STATUE_GREY] = STATUE_GREY_PATH,
	[STATUE_RED] = STATUE_RED_PATH,
	[EVIL_TREE] = EVIL_TREE_PATH,
	[MAIN_MENU] = MAIN_MENU_PATH,
	[PAUSE] = PAUSE_PATH,
	[DEATH] = DEATH_PATH,
	[CONTROLS] = CONTROLS_PATH,
	[WIN] = WIN_PATH,
	[STATUE_FACE] = STATUE_FACE_PATH,
	[CROSSBOW1] = CROSSBOW1_PATH,
	[CROSSBOW2] = CROSSBOW2_PATH,
	[EXIT_TEX] = EXIT_TEX_PATH,
	[AMMO_TEX] = AMMO_TEX_PATH
};

bool	resize_image(mlx_image_t *img, int img_i)
{
	if (img_i == SKY_TEX)
		return (mlx_resize_image(img, SKY_W, SKY_H));
	else if (img_i >= MAIN_MENU)
	{
		return (mlx_resize_image(img, WIN_W, WIN_H));
	}
	else
		return (mlx_resize_image(img, BLOCK_SIZE, BLOCK_SIZE));
}

void	*init_tex(t_mlx *mlx_data, mlx_texture_t **tex)
{
	mlx_image_t	**tex_img;
	int			i;

	tex_img = mlx_data->textrs_img;
	i = 0;
	while (i < MAX_TEX)
	{
		tex[i] = mlx_load_png(g_tex_path[i]);
		if (!tex[i])
			return (NULL);
		tex_img[i] = mlx_texture_to_image(mlx_data->mlx_ptr, tex[i]);
		if (!tex_img[i])
			return (NULL);
		if (!resize_image(tex_img[i], i))
			return (NULL);
		i++;
	}
	return (tex);
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
		{
			if (img == mlx_data->textrs_img[CROSSBOW2])
				img->enabled = false;
			mlx_set_instance_depth(&img->instances[0], 2);
		}
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
	put_img_to_win(data, mlx_data->textrs_img[MAIN_MENU]);
	put_img_to_win(data, mlx_data->textrs_img[PAUSE]);
	put_img_to_win(data, mlx_data->textrs_img[DEATH]);
	put_img_to_win(data, mlx_data->textrs_img[CONTROLS]);
	put_img_to_win(data, mlx_data->textrs_img[WIN]);
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
