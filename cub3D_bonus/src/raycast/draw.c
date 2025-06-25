/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:20:00 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/26 00:22:29 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_wall(t_raycast *raycast, int *ptr_y, t_wall *wall)
{
	int			tex_y;
	uint32_t	color;
	int			pixel_i;
	int			cur_y;

	cur_y = *ptr_y;
	while (cur_y < wall->top + wall->h && cur_y < (int)raycast->scr_img->height)
	{
		tex_y = (cur_y - wall->top) * BLOCK_SIZE / wall->h;
		pixel_i = (tex_y * wall->img->width + wall->tex_pos.x) * BPP;
		color = extract_rgba(&wall->img->pixels[pixel_i]);
		add_shadow(&color, raycast->data->rays_dist[raycast->cur_ray]);
		mlx_put_pixel(raycast->scr_img, raycast->cur_ray, cur_y, color);
		cur_y++;
	}
	*ptr_y = cur_y;
}

void	draw_sky(t_raycast *raycast, int y, int wall_top)
{
	mlx_image_t	*sky;
	t_point		tex;
	int			pixel_i;
	uint32_t	color;

	sky = raycast->data->mlx_data.textrs_img[SKY_TEX];
	tex.x = (raycast->ray_angle / 360.0) * sky->width;
	while (y < wall_top && y < (int)raycast->scr_img->height)
	{
		tex.y = sky->height - (raycast->plane->center.y - y);
		pixel_i = (tex.y * sky->width + tex.x) * BPP;
		color = extract_rgba(&sky->pixels[pixel_i]);
		mlx_put_pixel(raycast->scr_img, raycast->cur_ray, y, color);
		y++;
	}
}

void	draw_floor(t_raycast *raycast, int y)
{
	t_point		floor_pos;
	mlx_image_t	*img;
	int			pixel_i;
	uint32_t	color;
	int			dist;

	dist = 0;
	while (y < (int)raycast->scr_img->height)
	{
		img = fill_floor_info(raycast, &floor_pos, &dist, y);
		if (img)
		{
			floor_pos.x = floor_pos.x % BLOCK_SIZE;
			floor_pos.y = abs(floor_pos.y % BLOCK_SIZE);
			pixel_i = (floor_pos.y * img->width + floor_pos.x) * BPP;
			color = extract_rgba(&img->pixels[pixel_i]);
			add_shadow(&color, dist);
			mlx_put_pixel(raycast->scr_img, raycast->cur_ray, y, color);
		}
		y++;
	}
}

void	draw_ceiling(t_raycast *raycast, int wall_top, int y, int *p_y)
{
	t_point		ceil_pos;
	mlx_image_t	*img;
	int			pixel_i;
	uint32_t	color;
	int			dist;

	img = raycast->data->mlx_data.textrs_img[CEILING_TEX];
	dist = 0;
	while (y < (int)raycast->scr_img->height && y < wall_top)
	{
		fill_ceil_info(raycast, &ceil_pos, &dist, y);
		if (is_on_map(raycast->data, &ceil_pos) == true
			&& (raycast->unit_map[ceil_pos.y][ceil_pos.x] == FLOOR
			|| raycast->unit_map[ceil_pos.y][ceil_pos.x] == DOOR))
		{
			ceil_pos.x = ceil_pos.x % BLOCK_SIZE;
			ceil_pos.y = abs(ceil_pos.y % BLOCK_SIZE);
			pixel_i = (ceil_pos.y * img->width + ceil_pos.x) * BPP;
			color = extract_rgba(&img->pixels[pixel_i]);
			add_shadow(&color, dist);
			mlx_put_pixel(raycast->scr_img, raycast->cur_ray, y, color);
		}
		y++;
	}
	*p_y = y;
}

void	render_col(t_raycast *raycast, t_wall *wall)
{
	int	y;

	y = 0;
	fill_wall_info(raycast, wall);
	draw_sky(raycast, y, wall->top);
	draw_ceiling(raycast, wall->top, y, &y);
	draw_wall(raycast, &y, wall);
	draw_floor(raycast, y);
}
