/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:20:00 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/11 18:49:36 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	add_dark(t_raycast *raycast, uint32_t *color)
{
	double		inten;
	uint8_t		*raw_pixel;

	raw_pixel = (uint8_t *)color;
	inten = 1.0;
	raycast->wall.dist = raycast->rays_dist[raycast->cur_ray];

	if (raycast->wall.dist < BLOCK_SIZE)
	{

		inten = 1;
	}
	else if (raycast->wall.dist < BLOCK_SIZE * 2)
	{
		inten /= 2.0;
	}
	else if (raycast->wall.dist < BLOCK_SIZE * 3)
	{
		inten /= 3.0;
	}
	else if (raycast->wall.dist < BLOCK_SIZE * 4)
	{
		inten /= 4.0;
	}
	else if (raycast->wall.dist < BLOCK_SIZE * 5)
	{
		inten = 0.2;
	}
	else
	{
		inten = 0.1;
	}


	inten = (BLOCK_SIZE) / (double)raycast->wall.dist;

	if (inten > 1)
		inten = 1;

	raw_pixel[1] = raw_pixel[1] * inten;
	raw_pixel[2] = raw_pixel[2] * inten;
	raw_pixel[3] = raw_pixel[3] * inten;
}

void	map_wall(t_raycast *raycast, int y, int wall_h, int wall_top)
{
	int			tex_y;
	uint32_t	color;
	uint8_t		*raw_pixel;
	int			pixel_i;

	tex_y = (y - wall_top) * BLOCK_SIZE / wall_h;
	pixel_i = (tex_y * raycast->wall_img->width + raycast->tex_x) * BPP;
	raw_pixel = &raycast->wall_img->pixels[pixel_i];
	color = extract_rgba(raw_pixel);
	add_dark(raycast, &color);
	mlx_put_pixel(raycast->scr_img, raycast->cur_ray, y, color);
}
void	draw_floor(t_raycast *raycast, int y)
{
	double		dist;
	double		ratio;
	t_point		floor_tex;
	mlx_image_t	*img;
	int			texX;
	int			texY;
	int			pixel_i;
	uint32_t	color;
	uint8_t		*raw_pixel;

	img = raycast->data->mlx_data.textrs_img[FLOOR_TEX];
	double st = (double)BLOCK_SIZE / 4;
	while (y < raycast->scr_img->height)
	{
		ratio = st / (y - raycast->plane->center.y);
		dist = raycast->plane->dist * ratio;
		dist /= cos(deg_rad(raycast->beta));

		floor_tex.x = dist * cos(deg_rad(raycast->ray_angle));
		floor_tex.y = dist * -sin(deg_rad(raycast->ray_angle));

		floor_tex.x += raycast->char_pos.x;
		floor_tex.y += raycast->char_pos.y;

		texX = (int)floor(floor_tex.x) % BLOCK_SIZE;
		texY = abs((int)floor(floor_tex.y) % BLOCK_SIZE);

		pixel_i = (texY * img->width + texX) * BPP;
		raw_pixel = &img->pixels[pixel_i];
		color = extract_rgba(raw_pixel);
		mlx_put_pixel(raycast->scr_img, raycast->cur_ray, y, color);
		y++;
	}
}

void	render_col(t_raycast *raycast, t_wall *wall, int wall_dist,
		int tex_indx)
{
	int	wall_h;
	int	wall_top;
	int	y;

	wall_h = ceil(BLOCK_SIZE * raycast->plane->dist / (double)wall_dist);
	wall_top = raycast->plane->center.y;
	wall_top = wall_top - (wall_h / raycast->data->player.height);

	if (raycast->axis == HORIZONT)
	{
		raycast->tex_x = wall->pos.x % BLOCK_SIZE;
		if (wall->type == DOOR)
		{
			raycast->tex_x = BLOCK_SIZE - (wall->door_len - raycast->tex_x);
		}
	}
	else if (raycast->axis == VERTICAL)
	{
		raycast->tex_x = wall->pos.y % BLOCK_SIZE;
		if (wall->type == DOOR)
		{
			raycast->tex_x = BLOCK_SIZE - (wall->door_len - raycast->tex_x);
		}
	}

	raycast->wall_img = raycast->data->mlx_data.textrs_img[tex_indx];

	y = 0;
	while (y < raycast->scr_img->height)
	{
		if (y < wall_top )
			mlx_put_pixel(raycast->scr_img, raycast->cur_ray, y,
				raycast->ceil_rgbt);
		else if (y < wall_top + wall_h)
			map_wall(raycast, y, wall_h, wall_top);
		else
		{
			break ;
			// mlx_put_pixel(raycast->scr_img, raycast->cur_ray, y,
			// 	raycast->flor_rgbt);
		}
		y++;
	}
	draw_floor(raycast, y);
}
