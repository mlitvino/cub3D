/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:46:48 by mlitvino          #+#    #+#             */
/*   Updated: 2025/07/01 17:42:27 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	replace_unit_points(t_data *data, int grid_x, int grid_y)
{
	int		y;
	int		max_y;
	char	new_char;

	if (ft_strchr(FLOORS, data->grid_map[grid_y - 1][grid_x]))
		new_char = data->grid_map[grid_y - 1][grid_x];
	else if (ft_strchr(FLOORS, data->grid_map[grid_y + 1][grid_x]))
		new_char = data->grid_map[grid_y + 1][grid_x];
	else if (ft_strchr(FLOORS, data->grid_map[grid_y][grid_x + 1]))
		new_char = data->grid_map[grid_y][grid_x + 1];
	else if (ft_strchr(FLOORS, data->grid_map[grid_y][grid_x - 1]))
		new_char = data->grid_map[grid_y][grid_x - 1];
	else
		new_char = EMPTY;
	y = grid_y * BLOCK_SIZE;
	max_y = y + BLOCK_SIZE;
	while (y < max_y)
	{
		ft_memset(&data->unit_map[y][grid_x * BLOCK_SIZE], new_char,
			BLOCK_SIZE);
		y++;
	}
}

bool	resize_image(mlx_image_t *img, int img_i)
{
	int	hud_w;
	int	hud_h;

	hud_w = WIN_W / (double)HUD_W;
	hud_h = WIN_H / (double)HUD_H;
	if (img_i == SKY_TEX)
		return (mlx_resize_image(img, SKY_W, SKY_H));
	else if (img_i == HUD_TEX)
		return (mlx_resize_image(img, hud_w, hud_h));
	else if (img_i > HUD_TEX && img_i < MAIN_MENU)
		return (mlx_resize_image(img, hud_w / 4, hud_h / 1));
	else if (img_i >= MAIN_MENU)
		return (mlx_resize_image(img, WIN_W, WIN_H));
	else
		return (mlx_resize_image(img, BLOCK_SIZE, BLOCK_SIZE));
}
