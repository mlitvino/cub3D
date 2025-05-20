/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:43:06 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/20 19:18:02 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// typedef struct	s_raycast
// {
// 	double	cur_angle;
// 	int		view_angl;

// 	int		hor_grid_dist;
// 	int		ver_grid_dist;

// 	int		hor_wall_dist;
// 	int		ver_wall_dist;
// }				t_raycast;

// t_raycast	init_raycast(t_data *data, t_char *player)
// {
// 	t_raycast	rays_data;

// 	rays_data.cur_angle =
// }

bool	find_hor_wall(t_data *data, t_point *hor_grid_line, double ray_angl)
{
	t_point	char_pos;
	int		dx;
	int		dy;

	char_pos = data->player.pos;

	if ((0 < ray_angl) && (ray_angl < 180))
		dy = -BLOCK_SIZE;
	else
		dy = BLOCK_SIZE;
	dx = BLOCK_SIZE / tan(deg_rad(ray_angl));


	if (hor_grid_line->x == -1)
	{
		if ((0 < ray_angl) && (ray_angl < 180))
			hor_grid_line->y = (floor((double)char_pos.y / BLOCK_SIZE) * BLOCK_SIZE) - 1;
		else
			hor_grid_line->y = (floor((double)char_pos.y / BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE;
		hor_grid_line->x = char_pos.x + ((char_pos.y - hor_grid_line->y) / tan(deg_rad(ray_angl)));
	}
	else
	{
		hor_grid_line->x += dx;
		hor_grid_line->y += dy;
	}

	if (hor_grid_line->y >= data->map_h * BLOCK_SIZE
		|| hor_grid_line->x >= data->map_w * BLOCK_SIZE) // test check bound
	{
		ft_putstr_fd("ERROR: attempt to access outside of map\n", 2);
		exit(1);
	}

	if (data->unit_map[hor_grid_line->y][hor_grid_line->x] == WALL)
		return (true);

	//printf("%d + (%d - %d) / %f (tan(%f))\n", char_pos.x, char_pos.y, hor_grid_line->y, tan(60), ray_angl);
	// printf("grid x %d, grid y %d\n", hor_grid_line->x, hor_grid_line->y);
	// printf("x y %d\n", data->unit_map[hor_grid_line->y][hor_grid_line->x]);
	return (false);
}

bool	find_ver_wall(t_data *data, t_point *ver_grid_line, double ray_angl)
{
	t_point	char_pos;
	int		dx;
	int		dy;

	char_pos = data->player.pos;

	if ((0 < ray_angl) && (ray_angl < 180))
		dy = -BLOCK_SIZE;
	else
		dy = BLOCK_SIZE;
	dx = BLOCK_SIZE / tan(deg_rad(ray_angl));


	if (ver_grid_line->x == -1)
	{
		if ((0 < ray_angl) && (ray_angl < 180))
			ver_grid_line->y = (floor((double)char_pos.y / BLOCK_SIZE) * BLOCK_SIZE) - 1;
		else
			ver_grid_line->y = (floor((double)char_pos.y / BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE;
		ver_grid_line->x = char_pos.x + ((char_pos.y - ver_grid_line->y) / tan(deg_rad(ray_angl)));
	}
	else
	{
		ver_grid_line->x += dx;
		ver_grid_line->y += dy;
	}

	if (ver_grid_line->y >= data->map_h * BLOCK_SIZE
		|| ver_grid_line->x >= data->map_w * BLOCK_SIZE) // test check bound
	{
		ft_putstr_fd("ERROR: attempt to access outside of map\n", 2);
		exit(1);
	}

	if (data->unit_map[ver_grid_line->y][ver_grid_line->x] == WALL)
		return (true);
	return (false);
}

void	cast_ray(t_data *data, double ray_angl)
{
	t_point	hor_grid_line;
	t_point	ver_grid_line;

	ft_memset(&hor_grid_line, -1, sizeof(t_point));
	ft_memset(&ver_grid_line, -1, sizeof(t_point));
	while (find_hor_wall(data, &hor_grid_line, ray_angl) == false)
		;
	while (find_ver_wall(data, &ver_grid_line, ray_angl) == false)
		;

	// if (calc(hor_grid_line, data->player.pos) < calc(ver_grid_line, data->player.pos))
	// 	draw_hor_wall();
	// else
	// 	draw_ver_wall();
}



void	raycast(t_data *data)
{
	int			cur_ray;
	double		cur_angle;
	t_char		*player;

	player = &data->player;
	cur_ray = 0;
	player->pov.view_angl = 15;

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

		cast_ray(data, cur_angle);

		cur_ray++;
		cur_angle = cur_angle - data->rays_angle;
		if (cur_angle < 0)
			cur_angle = 360 + cur_angle;
	}
}
