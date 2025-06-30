/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:11:45 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/30 14:47:57 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_unit_map(t_data *data)
{
	int	y;
	int	x;

	data->unit_map = ft_calloc(data->map_h * BLOCK_SIZE, sizeof(char *));
	if (!data->unit_map)
		clean_all(data, "malloc");
	y = 0;
	while (y < data->map_h * BLOCK_SIZE)
	{
		data->unit_map[y] = ft_calloc(data->map_w * BLOCK_SIZE, sizeof(char));
		if (!data->unit_map[y])
			clean_all(data, "malloc");
		x = 0;
		while (x < data->map_w)
		{
			ft_memset(&data->unit_map[y][x * BLOCK_SIZE],
				data->grid_map[y / BLOCK_SIZE][x], BLOCK_SIZE);
			x++;
		}
		y++;
	}
}

void	init_player(t_data *data)
{
	t_char	*player;

	player = &data->player;
	player->data = data;
	player->hitbox_radius = BLOCK_SIZE / 4;
	player->height = BLOCK_SIZE / 2;
	player->move_spd = BLOCK_SIZE / 16;
	player->turn_spd = 2;
}

void	*init_tex(t_mlx *mlx_data, mlx_texture_t **tex)
{
	mlx_image_t	**tex_img;
	int			i;

	tex_img = mlx_data->textrs_img;
	i = 0;
	while (i < MAX_TEX)
	{
		tex[i] = mlx_load_png(mlx_data->tex_path[i]);
		if (!tex[i])
			return (NULL);
		tex_img[i] = mlx_texture_to_image(mlx_data->mlx_ptr, tex[i]);
		if (!tex_img[i])
			return (NULL);
		if (!mlx_resize_image(tex_img[i], BLOCK_SIZE, BLOCK_SIZE))
			return (NULL);
		i++;
	}
	return (*tex);
}

void	init_mlx(t_data *data)
{
	t_mlx	*mlx_data;

	mlx_data = &data->mlx_data;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_data->mlx_ptr = mlx_init(WIN_W, WIN_H, "cub3D", true);
	if (!mlx_data->mlx_ptr)
		clean_all(data, "mlx");
	mlx_data->scr_img = mlx_new_image(mlx_data->mlx_ptr, WIN_W, WIN_H);
	if (!mlx_data->scr_img)
		clean_all(data, "mlx");
	if (mlx_image_to_window(mlx_data->mlx_ptr, mlx_data->scr_img, 0, 0) < 0)
		clean_all(data, "mlx");
	if (!init_tex(mlx_data, mlx_data->textrs))
		clean_all(data, "mlx");
}

void	init_data(t_data *data)
{
	init_unit_map(data);
	init_player(data);
	init_mlx(data);
	data->plane.center.y = WIN_H / 2;
	data->plane.dist = (WIN_W / 2) / tan(deg_rad(FOV / 2));
	data->rays_count = WIN_W;
	data->rays_angle = FOV / (double)data->rays_count;
	data->flor_rgb.rgbt = (0xFF) | (data->flor_rgb.b << 8);
	data->flor_rgb.rgbt |= (data->flor_rgb.g << 16) | (data->flor_rgb.r << 24);
	data->ceil_rgb.rgbt = (0xFF) | (data->ceil_rgb.b << 8);
	data->ceil_rgb.rgbt |= (data->ceil_rgb.g << 16) | (data->ceil_rgb.r << 24);
}
