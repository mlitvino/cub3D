/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:55:28 by mlitvino          #+#    #+#             */
/*   Updated: 2025/07/01 16:51:55 by mlitvino         ###   ########.fr       */
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
[WOOD_WALL_TEX] = WOOD_WALL_PATH,
[STONE_WALL_TEX] = STONE_WALL_PATH,
[STONE_FLOOR_TEX] = STONE_FLOOR_PATH,
[DOOR_TEX] = DOOR_TEX_PATH,
[STONE_DOOR_TEX] = STONE_DOOR_PATH,
[MET_DOOR_TEX] = MET_DOOR_TEX_PATH,
[FLOOR_TEX] = FLOOR_TEX_PATH,
[BLD_GRASS_TEX] = BLD_GRASS_PATH,
[ROAD_TEX] = ROAD_PATH,
[GROUND_TEX] = GROUND_TEX_PATH,
[CEILING_TEX] = CEILING_TEX_PATH,
[SKY_TEX] = SKY_TEX_PATH,
[WOODPILE_TEX] = WOODPILE_PATH,
[BONES_TEX] = BONES_PATH,
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
[HUD_TEX] = HUD_PATH,
[N0_TEX] = N0_PATH,
[N1_TEX] = N1_PATH,
[N2_TEX] = N2_PATH,
[N3_TEX] = N3_PATH,
[N4_TEX] = N4_PATH,
[N5_TEX] = N5_PATH,
[N6_TEX] = N6_PATH,
[N7_TEX] = N7_PATH,
[N8_TEX] = N8_PATH,
[N9_TEX] = N9_PATH,
[CROSSBOW1] = CROSSBOW1_PATH,
[CROSSBOW2] = CROSSBOW2_PATH,
[EXIT_TEX] = EXIT_TEX_PATH,
[AMMO_TEX] = AMMO_TEX_PATH
};

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

void	init_hud(t_data *data, t_mlx *mlx_data, mlx_t *mlx)
{
	int			img_i;
	mlx_image_t	*img;
	int			hud_w;
	int			hud_h;

	img_i = HUD_TEX;
	hud_w = WIN_W / HUD_W;
	hud_h = WIN_H / HUD_H;
	img = mlx_data->textrs_img[img_i];
	if (mlx_image_to_window(mlx, img, 0, WIN_H - hud_h) < 0)
		clean_all(data, NULL);
	mlx_set_instance_depth(&img->instances[0], 1);
	while (++img_i < MAIN_MENU)
	{
		img = mlx_data->textrs_img[img_i];
		if (mlx_image_to_window(mlx, img, hud_w / 3, WIN_H - hud_h) < 0)
			clean_all(data, NULL);
		if (mlx_image_to_window(mlx, img, hud_w - hud_w / 4, WIN_H - hud_h) < 0)
			clean_all(data, NULL);
		mlx_set_instance_depth(&img->instances[0], 2);
		mlx_set_instance_depth(&img->instances[1], 2);
		img->instances[0].enabled = false;
		img->instances[1].enabled = false;
	}
}

void	put_img_to_win(t_data *data, mlx_image_t *img, int img_i)
{
	t_mlx	*mlx_data;

	mlx_data = &data->mlx_data;
	if (mlx_image_to_window(data->mlx_data.mlx_ptr, img, 0, 0) < 0)
		clean_all(data, NULL);
	if (img_i == CROSSBOW1 || img_i == CROSSBOW2 || img == mlx_data->minimap)
	{
		if (img_i == CROSSBOW2)
			img->enabled = false;
		mlx_set_instance_depth(&img->instances[0], 3);
	}
	else if (img_i == STATUE_FACE)
		mlx_set_instance_depth(&img->instances[0], 4);
	else if (img != mlx_data->scr_img)
	{
		mlx_set_instance_depth(&img->instances[0], 5);
		img->enabled = 0;
	}
}

bool	put_images_to_window(t_data *data, t_mlx *mlx_data)
{
	int	min_w;
	int	min_h;

	min_h = WIN_H / MINIMAP_H;
	min_w = WIN_W / MINIMAP_W;
	mlx_data->minimap = mlx_new_image(mlx_data->mlx_ptr, min_w, min_h);
	if (!mlx_data->minimap)
		clean_all(data, NULL);
	put_img_to_win(data, mlx_data->scr_img, -1);
	put_img_to_win(data, mlx_data->minimap, -1);
	put_img_to_win(data, mlx_data->textrs_img[CROSSBOW1], CROSSBOW1);
	put_img_to_win(data, mlx_data->textrs_img[CROSSBOW2], CROSSBOW2);
	put_img_to_win(data, mlx_data->textrs_img[STATUE_FACE], STATUE_FACE);
	put_img_to_win(data, mlx_data->textrs_img[MAIN_MENU], MAIN_MENU);
	put_img_to_win(data, mlx_data->textrs_img[PAUSE], PAUSE);
	put_img_to_win(data, mlx_data->textrs_img[DEATH], DEATH);
	put_img_to_win(data, mlx_data->textrs_img[CONTROLS], CONTROLS);
	put_img_to_win(data, mlx_data->textrs_img[WIN], WIN);
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
		clean_all(data, NULL);
	mlx_data->scr_img = mlx_new_image(mlx_data->mlx_ptr, WIN_W, WIN_H);
	if (!mlx_data->scr_img)
		clean_all(data, NULL);
	if (!init_tex(mlx_data, mlx_data->textrs))
		clean_all(data, NULL);
	put_images_to_window(data, &data->mlx_data);
	init_hud(data, &data->mlx_data, data->mlx_data.mlx_ptr);
	mlx_set_icon(mlx_data->mlx_ptr, mlx_data->textrs[WOLF_STAY]);
}
