/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:20:49 by mlitvino          #+#    #+#             */
/*   Updated: 2025/07/01 17:42:27 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	sort_sprite_dist(t_raycast *raycast, t_sprite **sprite_array)
{
	int			i;
	int			j;
	t_sprite	*temp;

	i = 0;
	while (i < raycast->sprite_count - 1)
	{
		j = i + 1;
		while (j < raycast->sprite_count)
		{
			if (sprite_array[i]->dist < sprite_array[j]->dist)
			{
				temp = sprite_array[i];
				sprite_array[i] = sprite_array[j];
				sprite_array[j] = temp;
			}
			j++;
		}
		i++;
	}
}

double	calc_angl_dif(t_raycast *raycast, t_sprite *srpite)
{
	t_point	rel;
	double	sprite_angle;
	double	angl_dif;

	rel.x = srpite->pos.x - raycast->char_pos.x;
	rel.y = srpite->pos.y - raycast->char_pos.y;
	sprite_angle = atan2(-rel.y, rel.x) * (180 / M_PI);
	if (sprite_angle < 0)
		sprite_angle += 360;
	else if (sprite_angle > 360)
		sprite_angle -= 360;
	angl_dif = raycast->view_angle + (FOV / 2) - sprite_angle;
	if (raycast->view_angle < 90 && sprite_angle > 270)
		angl_dif += 360;
	if (raycast->view_angle > 270 && sprite_angle < 90)
		angl_dif -= 360;
	if (angl_dif > -10 && angl_dif < FOV)
		srpite->dist *= cos(deg_rad(sprite_angle - raycast->view_angle));
	return (angl_dif);
}

void	calc_sprite(t_raycast *raycast, t_sprite **sprites)
{
	int		i;
	double	angl_dif;
	double	temp_h;
	double	h_ratio;

	i = 0;
	while (sprites[i])
	{
		sprites[i]->dist = calc_dist(raycast->char_pos, sprites[i]->pos);
		angl_dif = calc_angl_dif(raycast, sprites[i]);
		sprites[i]->size.x = angl_dif * (WIN_W / FOV);
		sprites[i]->size.y = raycast->plane->center.y;
		if (sprites[i]->dist < BLOCK_SIZE / 5)
			sprites[i]->dist = BLOCK_SIZE / 5;
		temp_h = BLOCK_SIZE * raycast->plane->dist / (double)sprites[i]->dist;
		sprites[i]->height = ceil(temp_h);
		sprites[i]->width = sprites[i]->height;
		sprites[i]->top = raycast->plane->center.y;
		h_ratio = 1 + (raycast->data->player.height / (BLOCK_SIZE / 2));
		sprites[i]->top -= (sprites[i]->height / h_ratio);
		sprites[i]->left = sprites[i]->size.x - (sprites[i]->width / 2);
		i++;
	}
}

void	draw_sprite_pix(t_raycast *raycast, t_sprite *sprite, int x, int y)
{
	uint32_t	color;
	int			pixel_i;
	t_point		tex_p;

	tex_p.x = (x - sprite->left) * BLOCK_SIZE / sprite->height;
	tex_p.y = (y - sprite->top) * BLOCK_SIZE / sprite->height;
	pixel_i = (tex_p.y * sprite->cur_img->width + tex_p.x) * BPP;
	color = extract_rgba(&sprite->cur_img->pixels[pixel_i]);
	add_shadow(&color, sprite->dist);
	if ((color & 0xFF) > 150)
		mlx_put_pixel(raycast->scr_img, x, y, color);
}

void	draw_sprite(t_raycast *raycast, t_sprite *sprite)
{
	int	cur_x;
	int	end_x;
	int	y;

	cur_x = sprite->left + raycast->thread_chunk * raycast->thrd_i;
	end_x = cur_x + raycast->thread_chunk + 1;
	if (cur_x < 0)
		cur_x = 0;
	while (cur_x < end_x && cur_x < sprite->left + sprite->width
		&& cur_x < WIN_W)
	{
		if (sprite->dist < raycast->data->rays_dist[cur_x])
		{
			y = sprite->top;
			if (y < 0)
				y = 0;
			while (y < sprite->top + sprite->height && y < WIN_H)
			{
				draw_sprite_pix(raycast, sprite, cur_x, y);
				y++;
			}
		}
		cur_x++;
	}
}
