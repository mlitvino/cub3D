/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:20:00 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/29 17:42:10 by mlitvino         ###   ########.fr       */
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
	wall_top = raycast->plane->center.y;
	wall_top = wall_top - (wall_h / raycast->data->player.height);
	if (raycast->tex_indx == NORTH || raycast->tex_indx == SOUTH)
		raycast->tex_x = wall.x % BLOCK_SIZE;
	else if (raycast->tex_indx == WEST || raycast->tex_indx == EAST)
		raycast->tex_x = wall.y % BLOCK_SIZE;
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
			mlx_put_pixel(raycast->scr_img, raycast->cur_ray, y,
				raycast->flor_rgbt);
		y++;
	}
}
