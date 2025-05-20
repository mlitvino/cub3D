/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:43:06 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/21 01:24:42 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// typedef struct	s_raycast
// {
// 	double	cur_angle;
// 	int		view_angl;

// 	int		hor_unit_dist;
// 	int		ver_unit_dist;

// 	int		hor_wall_dist;
// 	int		ver_wall_dist;
// }				t_raycast;

// t_raycast	init_raycast(t_data *data, t_char *player)
// {
// 	t_raycast	rays_data;

// 	rays_data.cur_angle =
// }

bool	find_hor_wall(t_data *data, t_point *hor_unit_line, double ray_angl)
{
	t_point	char_pos;
	int		dx;
	int		dy;

	char_pos = data->player.pos;

	if ((0 < ray_angl) && (ray_angl < 180))
		dy = -BLOCK_SIZE;
	else // CHECK IF ray_angl == 0 (straight to the right)
		dy = BLOCK_SIZE;
	dx = BLOCK_SIZE / tan(deg_rad(ray_angl));


	if (hor_unit_line->x == -1)
	{
		if ((0 < ray_angl) && (ray_angl < 180))
			hor_unit_line->y = (floor((double)char_pos.y / BLOCK_SIZE) * BLOCK_SIZE) - 1;
		else
			hor_unit_line->y = (floor((double)char_pos.y / BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE;
		hor_unit_line->x = char_pos.x + ((char_pos.y - hor_unit_line->y) / tan(deg_rad(ray_angl)));
	}
	else
	{
		hor_unit_line->x += dx;
		hor_unit_line->y += dy;
	}

	if (hor_unit_line->y >= data->map_h * BLOCK_SIZE
		|| hor_unit_line->x >= data->map_w * BLOCK_SIZE) // check bound of map
	{
		// printf("x %d, y %d , max x %d , max y %d\n", hor_unit_line->x, hor_unit_line->y,
		// 	data->map_w * BLOCK_SIZE, data->map_h * BLOCK_SIZE);
		// ft_putstr_fd("ERROR: attempt to access outside of map\n", 2);
		return (true);
		// printf("cur_angle %f\n", ray_angl);
		// printf("%d + (%d - %d) / %f (tan(%f))\n", char_pos.x, char_pos.y, hor_unit_line->y, tan(60), ray_angl);
		// printf("unit x %d, unit y %d\n", hor_unit_line->x, hor_unit_line->y);
		// printf("x y %d\n", data->unit_map[hor_unit_line->y][hor_unit_line->x]);
	}

	if (data->unit_map[hor_unit_line->y][hor_unit_line->x] == WALL)
		return (true);
	// printf("cur_angle %f\n", ray_angl);
	// printf("%d + (%d - %d) / %f (tan(%f))\n", char_pos.x, char_pos.y, hor_unit_line->y, tan(60), ray_angl);
	// printf("unit x %d, unit y %d\n", hor_unit_line->x, hor_unit_line->y);
	// printf("x y %d\n", data->unit_map[hor_unit_line->y][hor_unit_line->x]);

	return (false);
}

bool	find_ver_wall(t_data *data, t_point *ver_unit_line, double ray_angl)
{
	t_point	char_pos;
	int		dx;
	int		dy;

	char_pos = data->player.pos;

	if ((270 < ray_angl) || (ray_angl < 90))
		dx = BLOCK_SIZE;
	else
		dx = -BLOCK_SIZE;
	dy = BLOCK_SIZE / tan(deg_rad(ray_angl));


	if (ver_unit_line->x == -1)
	{
		if ((270 < ray_angl) || (ray_angl < 90))
			ver_unit_line->x = (floor((double)char_pos.x * BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE;
		else
			ver_unit_line->x = (floor((double)char_pos.x * BLOCK_SIZE) * BLOCK_SIZE) - 1;
		ver_unit_line->x = char_pos.y + ((char_pos.x - ver_unit_line->x) * tan(deg_rad(ray_angl)));
	}
	else
	{
		ver_unit_line->x += dx;
		ver_unit_line->y += dy;
	}

	if (ver_unit_line->y >= data->map_h * BLOCK_SIZE
		|| ver_unit_line->x >= data->map_w * BLOCK_SIZE) // test check bound
	{
		return (true);
		// printf("x %d, y %d , max x %d , max y %d\n", ver_unit_line->x, ver_unit_line->y,
		// 	data->map_w * BLOCK_SIZE, data->map_h * BLOCK_SIZE);
		// ft_putstr_fd("ERROR: attempt to access outside of map\n", 2);
	}

	if (data->unit_map[ver_unit_line->y][ver_unit_line->x] == WALL)
		return (true);
	return (false);
}

void	calc_dist(int view_angle, t_point char_pos, double ray_angl,
		t_point hor_unit_line, t_point ver_unit_line,
		int *hor_dist, int *ver_dist)
{
	double	beta;

	*hor_dist = abs(char_pos.x - hor_unit_line.x) / cos(deg_rad(ray_angl));
	*ver_dist = abs(char_pos.x - ver_unit_line.x) / cos(deg_rad(ray_angl));

	// remove fishbowl effect
	beta = ray_angl - view_angle;
	*hor_dist = *hor_dist * cos(deg_rad(beta));
	*ver_dist = *ver_dist * cos(deg_rad(beta));
}

void	draw_wall(t_data *data, double ray_angl, t_point wall)
{
	
}

void	cast_ray(t_data *data, double ray_angl)
{
	t_point	hor_unit_line;
	t_point	ver_unit_line;
	int		hor_dist;
	int		ver_dist;

	ft_memset(&hor_unit_line, -1, sizeof(t_point));
	ft_memset(&ver_unit_line, -1, sizeof(t_point));
	while (find_hor_wall(data, &hor_unit_line, ray_angl) == false)
		;
	while (find_ver_wall(data, &ver_unit_line, ray_angl) == false)
		;
	calc_dist(data->player.pov.view_angl, data->player.pos,
		ray_angl, hor_unit_line, ver_unit_line,
		&hor_dist, &ver_dist);
	if (hor_dist < ver_dist)
		draw_wall(data, ray_angl, hor_unit_line);
	else
		draw_wall(data, ray_angl, ver_unit_line);
}

void	raycast(t_data *data)
{
	int			cur_ray;
	double		cur_angle;
	t_char		*player;

	player = &data->player;
	cur_ray = 0;

	// t_raycast	rays_data;
	//rays_data = init_raycast(t_data *data);


	// printf("view_angle: %d\n", player->pov.view_angl); // del
	// printf("FOV / 2: %d\n", FOV / 2); // del
	// printf("min angle: %d\n", (player->pov.view_angl + (FOV / 2)) % 360); // del
	// printf("max angle: %d\n", (player->pov.view_angl - (FOV / 2)) % 360); // del
	// printf("rays_angle: %d\n", data->rays_angle); // del

	cur_angle = (player->pov.view_angl + (FOV / 2)) % 360;
	while (cur_ray < data->rays_count)
	{
		// printf("cur_ray: %d\n", cur_ray); // del
		// printf("rays_count: %d\n", data->rays_count); // del
		// printf("cur_angle: %f\n", cur_angle); // del

		//printf("cur_angle %f\n", cur_angle);
		cast_ray(data, cur_angle);

		cur_ray++;
		cur_angle = cur_angle - data->rays_angle;
		if (cur_angle < 0)
			cur_angle = 360 + cur_angle;
	}
}
