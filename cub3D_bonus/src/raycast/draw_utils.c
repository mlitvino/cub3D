/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:19:19 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/22 16:12:42 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	add_shadow(uint32_t *color, int dist)
{
	double	alpha_mod;
	uint8_t	*raw_pixel;

	raw_pixel = (uint8_t *)color;
	alpha_mod = (BLOCK_SIZE * MODIF_BRIGHT) / (double)dist;
	if (alpha_mod < 1)
	{
		*(++raw_pixel) *= alpha_mod;
		*(++raw_pixel) *= alpha_mod;
		*(++raw_pixel) *= alpha_mod;
	}
}

void	fill_wall_info(t_raycast *raycast, t_wall *wall)
{
	double	h_ratio;

	wall->h = ceil(BLOCK_SIZE * raycast->plane->dist / (double)wall->dist);
	wall->top = raycast->plane->center.y;
	h_ratio = 1 + (raycast->data->player.height / (BLOCK_SIZE / 2));
	wall->top = wall->top - (wall->h / h_ratio);
	if (raycast->axis == HORIZONT)
	{
		wall->tex_pos.x = wall->pos.x % BLOCK_SIZE;
		if (wall->type == DOOR)
			wall->tex_pos.x = BLOCK_SIZE - (wall->door_len - wall->tex_pos.x);
	}
	else if (raycast->axis == VERTICAL)
	{
		wall->tex_pos.x = wall->pos.y % BLOCK_SIZE;
		if (wall->type == DOOR)
			wall->tex_pos.x = BLOCK_SIZE - (wall->door_len - wall->tex_pos.x);
	}
	wall->img = raycast->data->mlx_data.textrs_img[wall->img_i];
}

void	fill_floor_info(t_raycast *raycast, t_point *ceil_pos, int *dist, int y)
{
	double		st;
	double		ratio;

	st = BLOCK_SIZE / (1 + ((BLOCK_SIZE / 2) / raycast->data->player.height));
	ratio = st / (y - raycast->plane->center.y);
	*dist = (raycast->plane->dist * ratio) / raycast->angl_table->beta;
	ceil_pos->x = (*dist * raycast->angl_table->cos) + raycast->char_pos.x;
	ceil_pos->y = (*dist * -raycast->angl_table->sin) + raycast->char_pos.y;
}

void	fill_ceil_info(t_raycast *raycast, t_point *ceil_pos, int *dist, int y)
{
	double		st;
	double		ratio;

	st = BLOCK_SIZE / (1 + ((BLOCK_SIZE / 2) / raycast->data->player.height));
	ratio = st / (raycast->plane->center.y - y);
	*dist = (raycast->plane->dist * ratio) / raycast->angl_table->beta;
	ceil_pos->x = (*dist * raycast->angl_table->cos) + raycast->char_pos.x;
	ceil_pos->y = (*dist * -raycast->angl_table->sin) + raycast->char_pos.y;
}
