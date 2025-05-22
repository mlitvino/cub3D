/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:43:06 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/22 18:00:00 by mlitvino         ###   ########.fr       */
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
	t_point		char_pos;
	double		dx;
	double		dy;


	char_pos = data->player.pos;

	if ((0 < ray_angl) && (ray_angl < 180))
		dy = -BLOCK_SIZE;
	else // CHECK IF ray_angl == 0 (straight to the right)
		dy = BLOCK_SIZE;



	if (270 < ray_angl || (180 < ray_angl && ray_angl < 270))
	{
		dx = -BLOCK_SIZE / tan(deg_rad(ray_angl));
	}
	else
	{
		dx = BLOCK_SIZE / tan(deg_rad(ray_angl));
	}


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
		|| hor_unit_line->y < 0 || hor_unit_line->x < 0
		|| hor_unit_line->x >= data->map_w * BLOCK_SIZE) // check bound of map
	{
		hor_unit_line->inval = true;
		// printf("x %d, y %d , max x %d , max y %d\n", hor_unit_line->x, hor_unit_line->y,
		// 	data->map_w * BLOCK_SIZE, data->map_h * BLOCK_SIZE);
		//ft_putstr_fd("ERROR: attempt to access outside of map\n", 2);
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

typedef struct	s_dpoint
{
	double	x;
	double	y;
}				t_dpoint;

bool	find_ver_wall(t_data *data, t_point *ver_unit_line, double ray_angl)
{
	t_point	char_pos;
	double		dx;
	double		dy;
	static		t_dpoint	temp;

	char_pos = data->player.pos;

	if (270 < ray_angl || ray_angl < 90)
	{
		dx = BLOCK_SIZE;
	}
	else
	{
		dx = -BLOCK_SIZE;
	}

	if (ray_angl < 90 || (180 < ray_angl && ray_angl < 270))
		dy = -BLOCK_SIZE * tan(deg_rad(ray_angl));
	else
		dy = BLOCK_SIZE * tan(deg_rad(ray_angl));


	//printf("\ndx %f dy %f\n", dx, dy);

	if (ver_unit_line->x == -1)
	{
		// temp.x = 0;
		// temp.y = 0;

		// if ((270 < ray_angl) || (ray_angl < 90))
		// 	temp.x = (ceil((double)char_pos.x / BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE;
		// else
		// 	temp.x = (ceil((double)char_pos.x / BLOCK_SIZE) * BLOCK_SIZE) - 1;
		// temp.y = char_pos.y + (char_pos.x - temp.x) * tan(deg_rad(ray_angl));

		if ((270 < ray_angl) || (ray_angl < 90))
			ver_unit_line->x = (floor(char_pos.x / (double)BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE;
		else
			ver_unit_line->x = (floor(char_pos.x / (double)BLOCK_SIZE) * BLOCK_SIZE) - 1;
		ver_unit_line->y = char_pos.y + (char_pos.x - ver_unit_line->x) * tan(deg_rad(ray_angl));
	}
	else
	{
		ver_unit_line->x += dx;
		ver_unit_line->y += dy;
		// temp.x += dx;
		// temp.y += dy;
	}
	// printf("find ver x %f y %f\n", temp.x, temp.y);
	//printf("find ver x %d y %d\n",ver_unit_line->x, ver_unit_line->y);

	// ver_unit_line->y = temp.y;
	// ver_unit_line->x = temp.x;

	if (ver_unit_line->y >= data->map_h * BLOCK_SIZE
		|| ver_unit_line->y < 0 || ver_unit_line->x < 0
		|| ver_unit_line->x >= data->map_w * BLOCK_SIZE) // test check bound
	{
		ver_unit_line->inval = true;
		// printf("ver x %d, y %d , max x %d , max y %d\n", ver_unit_line->x, ver_unit_line->y,
		// 	data->map_w * BLOCK_SIZE, data->map_h * BLOCK_SIZE);
		// ft_putstr_fd("ERROR: attempt to access outside of map\n", 2);
		return (true);
	}
		// printf("x %d, y %d , max x %d , max y %d\n", ver_unit_line->x, ver_unit_line->y,
		// 	data->map_w * BLOCK_SIZE, data->map_h * BLOCK_SIZE);
	//printf("map %d\n\n", data->unit_map[ver_unit_line->y][ver_unit_line->x]);
	if (data->unit_map[ver_unit_line->y][ver_unit_line->x] == WALL) // CCHECK CHECK
		return (true);
	return (false);
}

int	calc_dist(int view_angle, t_point char_pos, double ray_angl,
		t_point hor_unit_line, t_point ver_unit_line,
		int *hor_dist, int *ver_dist)
{
	double	beta;

	//printf("hor x %d y %d\n", hor_unit_line.x, hor_unit_line.y);
	//printf("ver x %d y %d\n", ver_unit_line.x, ver_unit_line.y);
	// *hor_dist = abs((char_pos.y - hor_unit_line.y) / cos(deg_rad(ray_angl)));
	// *ver_dist = abs((char_pos.x - ver_unit_line.x) / cos(deg_rad(ray_angl)));

	*hor_dist = root_dist(char_pos, hor_unit_line);
	*ver_dist = root_dist(char_pos, ver_unit_line);


	//remove fishbowl effect
	//printf("before calc hor %d ver %d\n", *hor_dist, *ver_dist); // del
	beta = ray_angl - view_angle;
	*hor_dist = *hor_dist * cos(deg_rad(beta));
	*ver_dist = *ver_dist * cos(deg_rad(beta));

	*hor_dist = root_dist(char_pos, hor_unit_line) * cos(deg_rad(beta));
	*ver_dist = root_dist(char_pos, ver_unit_line) * cos(deg_rad(beta));
	//printf("after calc hor %d ver %d\n", *hor_dist, *ver_dist); // del

	if (hor_unit_line.inval == true)
		*hor_dist = INT_MAX;

	if (ver_unit_line.inval == true)
		*ver_dist = INT_MAX;

	if (*ver_dist < *hor_dist)
		return (*ver_dist);
	else
		return (*hor_dist);
}

void	map_wall(t_data *data, double ray_angl, t_point wall, int wall_dist, int cur_ray, int i, int wall_h, int wall_top)
{
	// int	offset;
	// mlx_image_t	*wall_img;

	// if (wall.y % (BLOCK_SIZE) == 0)
	// {
	// 	offset = wall.x % BLOCK_SIZE;
	// }
	// else if (wall.x % (BLOCK_SIZE) == 0)
	// {
	// 	offset = wall.y % BLOCK_SIZE;
	// }

	// wall_img = data->mlx_data.textrs_img[NORTH];

	// int	tex_y = (i - wall_top) *
	// int	wall_rgbt = wall_img->pixels[(i * BLOCK_SIZE + offset) * BPP];

	// mlx_put_pixel(data->mlx_data.scr_img, cur_ray, i, wall_rgbt);
    int tex_x, tex_y;
    mlx_image_t *wall_img = data->mlx_data.textrs_img[NORTH];

    // pick the correct wall‐slice (x in texture)
    if (wall.y % BLOCK_SIZE == 0)
        tex_x = wall.x % BLOCK_SIZE;
    else
        tex_x = wall.y % BLOCK_SIZE;

    // map screen‐y (i) to texture‐y; assume wall_h and wall_top are in scope
    tex_y = (i - wall_top) * BLOCK_SIZE / wall_h;

    // clamp
    if (tex_x < 0) tex_x = 0; else if (tex_x >= wall_img->width)  tex_x = wall_img->width - 1;
    if (tex_y < 0) tex_y = 0; else if (tex_y >= wall_img->height) tex_y = wall_img->height - 1;

    // index by pixels[y*width + x]
    uint32_t color = ((uint32_t*)wall_img->pixels)[ tex_y * wall_img->width + tex_x ];
    mlx_put_pixel(data->mlx_data.scr_img, cur_ray, i, color);
}

void	draw_wall(t_data *data, double ray_angl, t_point wall, int wall_dist,
			int cur_ray)
{
	int			wall_h;
	int			wall_top;
	int			wall_rgbt;
	mlx_image_t	*scr_img;
	t_project	plane;
	int			i;

	plane = data->plane;
	scr_img = data->mlx_data.scr_img;
	wall_h = ceil(BLOCK_SIZE * data->plane.dist / (double)wall_dist); // rounded up?
	wall_top = plane.center.y - (wall_h / 2);
	wall_rgbt = 0xd333fff5;

	// printf("p cen y %d\n", plane.center.y);
	// printf("cur ray %d\n", cur_ray); // del
	// printf("wall x %d wall y %d\n", wall.x, wall.y);
	// printf("wall_dist %d\n", wall_dist);
	// printf("wall_h %d\n", wall_h);
	// printf("wall_top %d\n", wall_top);
	// printf("max x %d , max y %d\n", data->map_w * BLOCK_SIZE, data->map_h * BLOCK_SIZE);
	// printf("---\n");

	i = 0;
	while (i < scr_img->height)
	{
		if (i < wall_top)
			mlx_put_pixel(scr_img, cur_ray, i, data->cell_rgb.rgbt);
		else if (i <= wall_top + wall_h)
			map_wall(data, ray_angl, wall, wall_dist, cur_ray, i, wall_h, wall_top);
		else
			mlx_put_pixel(scr_img, cur_ray, i, data->floor_rgb.rgbt);
		i++;
	}
}

void	cast_ray(t_data *data, double ray_angl, int cur_ray)
{
	t_point	hor_unit_line;
	t_point	ver_unit_line;
	int		hor_dist;
	int		ver_dist;

	ft_memset(&hor_unit_line, -1, sizeof(t_point));
	ft_memset(&ver_unit_line, -1, sizeof(t_point));

	if ((int)ray_angl == 180 || (int)ray_angl == 0)
	{
		hor_unit_line.inval = true;
	}
	if ((int)ray_angl == 90 || (int)ray_angl == 270)
	{
		ver_unit_line.inval = true;
	}

	if ((int)ray_angl != 180 && (int)ray_angl != 0)
		while (find_hor_wall(data, &hor_unit_line, ray_angl) == false)
			;
	if ((int)ray_angl != 270 && (int)ray_angl != 90)
		while (find_ver_wall(data, &ver_unit_line, ray_angl) == false)
			;
	int dist = calc_dist(data->player.pov.view_angl, data->player.pos,
		ray_angl, hor_unit_line, ver_unit_line,
		&hor_dist, &ver_dist);

	if (hor_unit_line.inval == true)
		hor_dist = INT_MAX;

	if (ver_unit_line.inval == true)
		ver_dist = INT_MAX;

	if (hor_dist < ver_dist)
		draw_wall(data, ray_angl, hor_unit_line, hor_dist, cur_ray);
	else
		draw_wall(data, ray_angl, ver_unit_line, ver_dist, cur_ray);
}

void	raycast(t_data *data)
{
	int			cur_ray;
	double		cur_angle;
	t_char		*player;

	player = &data->player;


	// t_raycast	rays_data;
	//rays_data = init_raycast(t_data *data);


	// printf("view_angle: %d\n", player->pov.view_angl); // del
	// printf("FOV / 2: %d\n", FOV / 2); // del
	// printf("min angle: %d\n", (player->pov.view_angl + (FOV / 2)) % 360); // del
	// printf("max angle: %d\n", (player->pov.view_angl - (FOV / 2)) % 360); // del
	// printf("rays_angle: %d\n", data->rays_angle); // del
	cur_ray = 0;
	cur_angle = (player->pov.view_angl + (FOV / 2)) % 360;
	// cur_angle = 0;
	while (cur_ray < data->rays_count)
	{
		//printf("cur_ray: %d\n", cur_ray); // del
		//printf("rays_count: %d\n", data->rays_count); // del
		//printf("cur_angle: %f\n", cur_angle); // del

		cast_ray(data, cur_angle, cur_ray);

		cur_ray++;
		cur_angle = cur_angle - data->rays_angle;
		if (cur_angle < 0)
			cur_angle = 360 + cur_angle;
		// if (cur_ray == 2)
		// 	break ;
	}
}
