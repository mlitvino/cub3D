/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:43:06 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/25 15:05:28 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_on_map(t_data *data, t_point *p)
{
	return ((0 <= p->x && p->x < data->map_w * BLOCK_SIZE)
		&& (0 <= p->y && p->y < data->map_h * BLOCK_SIZE));
}

bool	find_hor_wall(t_data *data, t_point *hor_unit_line, double ray_angl, int *hor_dist)
{
	t_point		char_pos;
	double		dx;
	double		dy;
	t_dpoint	temp;


	char_pos = data->player.pos;
	if ((0 < ray_angl) && (ray_angl < 180))
	{
		dx = BLOCK_SIZE / tan(deg_rad(ray_angl));
		dy = -BLOCK_SIZE;
	}
	else
	{
		dx = -BLOCK_SIZE / tan(deg_rad(ray_angl));
		dy = BLOCK_SIZE;
	}
	while (1)
	{
		if (hor_unit_line->x == -1)
		{
			if ((0 < ray_angl) && (ray_angl < 180))
				temp.y = (floor((double)char_pos.y / BLOCK_SIZE) * BLOCK_SIZE) - 1;
			else
				temp.y = (floor((double)char_pos.y / BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE;
			temp.x = char_pos.x + ((char_pos.y - temp.y) / tan(deg_rad(ray_angl)));
		}
		else
		{
			temp.x += dx;
			temp.y += dy;
		}

		if (270 < ray_angl || ray_angl < 90)
		{
			hor_unit_line->x = temp.x;
			hor_unit_line->y = temp.y;

		}
		else
		{
			hor_unit_line->x = ceil(temp.x);
			hor_unit_line->y = ceil(temp.y);
		}

		if (is_on_map(data, hor_unit_line) == false)
		{
			*hor_dist = INT_MAX;
			return (true);
		}

		if (data->unit_map[hor_unit_line->y][hor_unit_line->x] == WALL)
			return (true);
	}
	return (false);
}

bool	find_ver_wall(t_data *data, t_point *ver_unit_line, double ray_angl, int *ver_dist)
{
	t_point		char_pos;
	double		dx;
	double		dy;
	t_dpoint	temp;

	char_pos = data->player.pos;

	if (270 < ray_angl || ray_angl < 90)
	{
		dx = BLOCK_SIZE;
		dy = -BLOCK_SIZE * tan(deg_rad(ray_angl));
	}
	else
	{
		dx = -BLOCK_SIZE;
		dy = BLOCK_SIZE * tan(deg_rad(ray_angl));
	}

	while (1)
	{
		if (ver_unit_line->x == -1)
		{
			if ((270 < ray_angl) || (ray_angl < 90))
				temp.x = (floor((double)char_pos.x / BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE;
			else
				temp.x = (floor((double)char_pos.x / BLOCK_SIZE) * BLOCK_SIZE) - 1;
			temp.y = char_pos.y + (char_pos.x - temp.x) * tan(deg_rad(ray_angl));
		}
		else
		{
			temp.x += dx;
			temp.y += dy;
		}

		if (ray_angl < 180)
		{
			ver_unit_line->x = ceil(temp.x);
			ver_unit_line->y = ceil(temp.y);
		}
		else
		{
			ver_unit_line->x = temp.x;
			ver_unit_line->y = temp.y;
		}

		if (is_on_map(data, ver_unit_line) == false) // test check bound
		{
			*ver_dist = INT_MAX;
			return (true);
		}
		if (data->unit_map[ver_unit_line->y][ver_unit_line->x] == WALL) // CCHECK CHECK
			return (true);
	}
	return (false);
}

void	map_wall(t_raycast *raycast, t_point wall, int y, int wall_h, int wall_top, int tex_indx)
{
	int			tex_x;
	int			tex_y;
	mlx_image_t	*wall_img;
	uint32_t	color;
	uint8_t		*raw_pixel;

	if (tex_indx == NORTH || tex_indx == SOUTH)
		tex_x = wall.x % BLOCK_SIZE;
	else if (tex_indx == WEST || tex_indx == EAST)
		tex_x = wall.y % BLOCK_SIZE;

	wall_img = raycast->data->mlx_data.textrs_img[tex_indx];
	tex_y = (y - wall_top) * BLOCK_SIZE / wall_h;
	raw_pixel = &wall_img->pixels[(tex_y * wall_img->width + tex_x) * BPP];
	color = extract_rgba(raw_pixel);
	mlx_put_pixel(raycast->data->mlx_data.scr_img, raycast->cur_ray, y, color);
}

void	draw_wall(t_raycast *raycast, t_point wall, int wall_dist, int tex_indx)
{
	int			wall_h;
	int			wall_top;
	int			y;

	wall_h = ceil(BLOCK_SIZE * raycast->plane->dist / (double)wall_dist); // rounded up?
	wall_top = raycast->plane->center.y - (wall_h / 2);
	y = 0;
	while (y < raycast->scr_img->height)
	{
		if (y < wall_top)
			mlx_put_pixel(raycast->scr_img, raycast->cur_ray, y, raycast->data->cell_rgb.rgbt);
		else if (y <= wall_top + wall_h)
		{
			map_wall(raycast, wall, y, wall_h, wall_top, tex_indx);
			//mlx_put_pixel(raycast->scr_img, raycast->cur_ray, y, 0xFF);
		}
		else
			mlx_put_pixel(raycast->scr_img, raycast->cur_ray, y, raycast->data->floor_rgb.rgbt);
		y++;
	}
}

int	calc_dist(t_raycast *raycast,
		t_point hor_unit_line, t_point ver_unit_line,
		int *hor_dist, int *ver_dist)
{
	double	temp;

	if (*hor_dist != INT_MAX)
	{
		temp = root_dist(raycast->char_pos, hor_unit_line);
		*hor_dist = temp * cos(deg_rad(raycast->beta));
	}
	if (*ver_dist != INT_MAX)
	{
		temp = root_dist(raycast->char_pos, ver_unit_line);
		*ver_dist = temp * cos(deg_rad(raycast->beta));
	}
}

void	select_tex(int *tex_indx, int ray_angl, int line_flag)
{
	if (line_flag == VERTICAL)
	{
		if (90 < ray_angl && ray_angl < 270)
			*tex_indx = EAST;
		else
			*tex_indx = WEST;
	}
	else
	{
		if ((0 < ray_angl) && (ray_angl < 180))
			*tex_indx = SOUTH;
		else
			*tex_indx = NORTH;
	}
}

void	compre_dist(t_raycast *raycast, t_point hor_unit_line, t_point ver_unit_line,
		int hor_dist, int ver_dist)
{
	int	tex_indx;
	int	ray_angl;

	ray_angl = raycast->ray_angle;
	if (hor_dist < ver_dist)
	{
		select_tex(&tex_indx, ray_angl, HORIZONT);
		draw_wall(raycast, hor_unit_line, hor_dist, tex_indx);
	}
	else if (ver_dist < hor_dist)
	{
		select_tex(&tex_indx, ray_angl, VERTICAL);
		draw_wall(raycast, ver_unit_line, ver_dist, tex_indx);
	}
	else if (raycast->unit_map[hor_unit_line.y][hor_unit_line.x - 1] == WALL
			&& raycast->unit_map[hor_unit_line.y][hor_unit_line.x + 1] == WALL)
	{
		select_tex(&tex_indx, ray_angl, HORIZONT);
		draw_wall(raycast, hor_unit_line, hor_dist, tex_indx);
	}
	else
	{
		select_tex(&tex_indx, ray_angl, VERTICAL);
		draw_wall(raycast, ver_unit_line, ver_dist, tex_indx);
	}
}

void	cast_ray(t_data *data, t_raycast *raycast, double ray_angl, int cur_ray)
{
	t_point	hor_unit_line;
	t_point	ver_unit_line;
	int		hor_dist;
	int		ver_dist;

	ft_memset(&hor_unit_line, -1, sizeof(t_point));
	ft_memset(&ver_unit_line, -1, sizeof(t_point));
	hor_dist = 0;
	ver_dist = 0;
	if ((int)ray_angl != 180 && (int)ray_angl != 0)
		find_hor_wall(data, &hor_unit_line, ray_angl, &hor_dist);
	else
		hor_dist = INT_MAX;
	if ((int)ray_angl != 90 && (int)ray_angl != 270)
		find_ver_wall(data, &ver_unit_line, ray_angl, &ver_dist);
	else
		ver_dist = INT_MAX;
	calc_dist(raycast, hor_unit_line, ver_unit_line, &hor_dist, &ver_dist);
	compre_dist(raycast, hor_unit_line, ver_unit_line, hor_dist, ver_dist);
}

t_raycast	init_raycast(t_data *data, t_char *player)
{
	t_raycast	raycast;

	raycast.data = data;
	raycast.plane = &data->plane;
	raycast.scr_img = data->mlx_data.scr_img;
	raycast.unit_map = data->unit_map;

	raycast.ray_angle = (player->pov.view_angl + (FOV / 2)) % 360;
	raycast.cur_ray = 0;

	raycast.view_angle = player->pov.view_angl;
	raycast.char_pos = player->pos;

	return (raycast);
}

void	fill_ray_info(t_raycast *raycast)
{
	raycast->beta = raycast->ray_angle - raycast->view_angle;
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
		cast_ray(data, &raycast, raycast.ray_angle, cur_ray);
		cur_ray++;
		cur_angle -= data->rays_angle;
		if (cur_angle < 0)
			cur_angle = 360 + cur_angle;
		raycast.ray_angle = cur_angle;
		raycast.cur_ray = cur_ray;
	}
}
