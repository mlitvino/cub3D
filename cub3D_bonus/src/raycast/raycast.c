/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:43:06 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/06 15:09:33 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	compre_dist(t_raycast *raycast, t_wall *hor_wall, t_wall *ver_wall)
{
	if (hor_wall->dist < ver_wall->dist)
	{
		raycast->rays_dist[raycast->cur_ray] = hor_wall->dist;
		raycast->axis = HORIZONT;
		select_tex(raycast, hor_wall, HORIZONT);
		render_col(raycast, hor_wall, hor_wall->dist, raycast->tex_indx);
	}
	else if (ver_wall->dist < hor_wall->dist)
	{
		raycast->rays_dist[raycast->cur_ray] = ver_wall->dist;
		raycast->axis = VERTICAL;
		select_tex(raycast, ver_wall, VERTICAL);
		render_col(raycast, ver_wall, ver_wall->dist, raycast->tex_indx);
	}
	else if (hor_wall->dist != INT_MAX
		&& raycast->unit_map[hor_wall->pos.y][hor_wall->pos.x - 1] == WALL
		&& raycast->unit_map[hor_wall->pos.y][hor_wall->pos.x + 1] == WALL)
	{
		raycast->rays_dist[raycast->cur_ray] = hor_wall->dist;
		raycast->axis = HORIZONT;
		select_tex(raycast, hor_wall, HORIZONT);
		render_col(raycast, hor_wall, hor_wall->dist, raycast->tex_indx);
	}
	else
	{
		raycast->rays_dist[raycast->cur_ray] = ver_wall->dist;
		raycast->axis = VERTICAL;
		select_tex(raycast, ver_wall, VERTICAL);
		render_col(raycast, ver_wall, ver_wall->dist, raycast->tex_indx);
	}
}

void	cast_ray(t_raycast *raycast, double ray_angl)
{
	if ((int)ray_angl != 180 && (int)ray_angl != 0)
		find_wall(raycast, &raycast->hor_wall, HORIZONT);
	else
		raycast->hor_wall.dist = INT_MAX;
	if ((int)ray_angl != 90 && (int)ray_angl != 270)
		find_wall(raycast, &raycast->ver_wall, VERTICAL);
	else
		raycast->ver_wall.dist = INT_MAX;
	calc_norm_dist(raycast);
	compre_dist(raycast, &raycast->hor_wall, &raycast->ver_wall);
}

t_sprite	**init_spite_array(t_raycast *raycast)
{
	t_sprite	**sprite_array;
	t_sprite	*temp;
	int			sprite_count;

	sprite_count = 0;
	temp = raycast->data->sprite_list;
	while (temp)
	{
		sprite_count++;
		temp = temp->next;
	}
	sprite_array = ft_calloc(sprite_count + 1, sizeof(t_sprite *));
	if (!sprite_array)
		clean_all(raycast->data);
	raycast->sprite_count = sprite_count;
	sprite_count = 0;
	temp = raycast->data->sprite_list;
	while (temp)
	{
		sprite_array[sprite_count++] = temp;
		temp = temp->next;
	}
	return (sprite_array);
}

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

void	calc_sprite(t_raycast *raycast, t_sprite **sprites)
{
	int		i;
	t_point	rel;
	double	q;

	i = 0;
	while (i < raycast->sprite_count)
	{
		sprites[i]->dist = calc_dist(raycast->char_pos, sprites[i]->pos);
		i++;
	}
}

void	calc_sprite_size(t_raycast *raycast, t_sprite **sprite_array)
{
	t_point	rel;
	t_sprite *test = sprite_array[0];
	double	sprte_angle;
	double	q;

	rel.x = test->pos.x - raycast->char_pos.x;
	rel.y = test->pos.y - raycast->char_pos.y;
	sprte_angle = atan2(-rel.y, rel.x) * (180 / M_PI);
	if (sprte_angle < 0)
		sprte_angle += 360;
	else if (sprte_angle > 360)
		sprte_angle -= 360;
	q = raycast->view_angle + (FOV / 2) - sprte_angle;
	if (raycast->view_angle < 90 && sprte_angle > 270)
		q += 360;
	if (raycast->view_angle > 270 && sprte_angle < 90)
		q -= 360;

	if (q > -10 && q < FOV * 1.5)
		test->dist = test->dist * cos(deg_rad(sprte_angle - raycast->view_angle));

	printf("view angle %d\n", raycast->view_angle);
	printf("sprite_angle %f\n", sprte_angle);
	printf("q %f\n", q);

	test->size.x = q * (WIN_W / FOV);
	test->size.y = raycast->plane->center.y;

	if (test->dist < BLOCK_SIZE / 5)
	{
		test->dist = BLOCK_SIZE / 5;
	}

	test->height = ceil(BLOCK_SIZE * raycast->plane->dist / (double)test->dist);


	ft_printf("test h %d\n", test->height);
	ft_printf("test dist %d\n", test->dist);
	int test_width = test->height;

	int test_top = raycast->plane->center.y;
	test_top = test_top - (test->height / 2);
	int	test_left = test->size.x - (test_width / 2);



	int tex_x;
	int tex_y;
	int x = test_left;
	int y;
	int pixel_i;
	uint32_t	color;
	uint8_t		*raw_pixel;
	if (x < 0)
	{
		x = 0;
	}
	while (x < test_left + test_width && x < WIN_W)
	{
		if (test->dist < raycast->rays_dist[x])
		{
			tex_x = (x - test_left) * BLOCK_SIZE / test->height;

			y = test_top;
			if (y < 0)
			{
				y = 0;
			}
			while (y < test_top + test->height && y < WIN_H)
			{
				tex_y = (y - test_top) * BLOCK_SIZE / test->height;

				pixel_i = (tex_y * test->tex_imgs[WOLF_STAY]->width + tex_x) * BPP;
				raw_pixel = &test->tex_imgs[WOLF_STAY]->pixels[pixel_i];
				color = extract_rgba(raw_pixel);
				if (color | 0x00)
					mlx_put_pixel(raycast->scr_img, x, y, color);
				y++;
			}
		}
		x++;
	}
}

void	handle_sprites(t_raycast *raycast)
{
	t_sprite	**sprite_array;

	sprite_array = init_spite_array(raycast);
	calc_sprite(raycast, sprite_array);
	//show_sprites(sprite_array, NULL);
	sort_sprite_dist(raycast, sprite_array);
	//show_sprites(sprite_array, NULL);
	calc_sprite_size(raycast, sprite_array);
	free(sprite_array);
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
	if (data->sprite_list)
		handle_sprites(&raycast);
}
