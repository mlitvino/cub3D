/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:43:06 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/16 14:20:55 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	mlx_put_pixel(raycast->scr_img, raycast->cur_ray, y, color);
}

void	render_col(t_raycast *raycast, t_point wall, int wall_dist,
		int tex_indx)
{
	int	wall_h;
	int	wall_top;
	int	y;

	wall_h = ceil(BLOCK_SIZE * raycast->plane->dist / (double)wall_dist);
	wall_top = raycast->plane->center.y - (wall_h / 2);
	if (raycast->tex_indx == NORTH || raycast->tex_indx == SOUTH)
		raycast->tex_x = wall.x % BLOCK_SIZE;
	else if (raycast->tex_indx == WEST || raycast->tex_indx == EAST)
		raycast->tex_x = wall.y % BLOCK_SIZE;
	raycast->wall_img = raycast->data->mlx_data.textrs_img[tex_indx];
	y = 0;
	while (y < (int)raycast->scr_img->height)
	{
		if (y < wall_top)
			mlx_put_pixel(raycast->scr_img, raycast->cur_ray, y,
				raycast->ceil_rgbt);
		else if (y < wall_top + wall_h)
			map_wall(raycast, y, wall_h, wall_top);
		else
			mlx_put_pixel(raycast->scr_img, raycast->cur_ray, y,
				raycast->flor_rgbt);
		y++;
	}
}

void	compre_dist(t_raycast *raycast, t_point hor_wall, t_point ver_wall)
{
	if (raycast->hor_dist < raycast->ver_dist)
	{
		select_tex(raycast, HORIZONT);
		render_col(raycast, hor_wall, raycast->hor_dist, raycast->tex_indx);
	}
	else if (raycast->ver_dist < raycast->hor_dist)
	{
		select_tex(raycast, VERTICAL);
		render_col(raycast, ver_wall, raycast->ver_dist, raycast->tex_indx);
	}
	else if (raycast->hor_dist != INT_MAX
		&& raycast->unit_map[hor_wall.y][hor_wall.x - 1] == WALL
		&& raycast->unit_map[hor_wall.y][hor_wall.x + 1] == WALL)
	{
		select_tex(raycast, HORIZONT);
		render_col(raycast, hor_wall, raycast->hor_dist, raycast->tex_indx);
	}
	else
	{
		select_tex(raycast, VERTICAL);
		render_col(raycast, ver_wall, raycast->ver_dist, raycast->tex_indx);
	}
}

void	cast_ray(t_raycast *raycast, double ray_angl)
{
	if ((int)ray_angl != 180 && (int)ray_angl != 0)
		find_wall(raycast, &raycast->hor_wall, HORIZONT, &raycast->hor_dist);
	else
		raycast->hor_dist = INT_MAX;
	if ((int)ray_angl != 90 && (int)ray_angl != 270)
		find_wall(raycast, &raycast->ver_wall, VERTICAL, &raycast->ver_dist);
	else
		raycast->ver_dist = INT_MAX;
	calc_norm_dist(raycast);
	compre_dist(raycast, raycast->hor_wall, raycast->ver_wall);
}

void	raycast(t_data *data)
{
	t_raycast	raycast;
	int			cur_ray;
	double		cur_angle;

	raycast = init_raycast(data, &data->player);
	cur_ray = 0;
	cur_angle = raycast.ray_angle;
	while (cur_ray < data->rays_count)
	{
		fill_ray_info(&raycast);
		cast_ray(&raycast, raycast.ray_angle);
		cur_ray++;
		cur_angle -= data->rays_angle;
		if (cur_angle < 0)
			cur_angle = 360 + cur_angle;
		raycast.ray_angle = cur_angle;
		raycast.cur_ray = cur_ray;
	}
}
