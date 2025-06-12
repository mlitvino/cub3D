/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:43:06 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/12 18:20:26 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	compre_dist(t_raycast *raycast, t_wall *hor_wall, t_wall *ver_wall)
{
	if (hor_wall->dist < ver_wall->dist)
	{
		raycast->data->rays_dist[raycast->cur_ray] = hor_wall->dist;
		raycast->axis = HORIZONT;
		select_tex(raycast, hor_wall, HORIZONT);
		render_col(raycast, hor_wall, hor_wall->dist, raycast->tex_indx);
	}
	else if (ver_wall->dist < hor_wall->dist)
	{
		raycast->data->rays_dist[raycast->cur_ray] = ver_wall->dist;
		raycast->axis = VERTICAL;
		select_tex(raycast, ver_wall, VERTICAL);
		render_col(raycast, ver_wall, ver_wall->dist, raycast->tex_indx);
	}
	else if (hor_wall->dist != INT_MAX
		&& raycast->unit_map[hor_wall->pos.y][hor_wall->pos.x - 1] == WALL
		&& raycast->unit_map[hor_wall->pos.y][hor_wall->pos.x + 1] == WALL)
	{
		raycast->data->rays_dist[raycast->cur_ray] = hor_wall->dist;
		raycast->axis = HORIZONT;
		select_tex(raycast, hor_wall, HORIZONT);
		render_col(raycast, hor_wall, hor_wall->dist, raycast->tex_indx);
	}
	else
	{
		raycast->data->rays_dist[raycast->cur_ray] = ver_wall->dist;
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

void	handle_sprites(t_raycast *raycast)
{
	t_sprite	**sprite_array;
	int			i;
	int			thrd_i;

	sprite_array = init_spite_array(raycast);
	calc_sprite(raycast, sprite_array);
	sort_sprite_dist(raycast, sprite_array);
	i = 0;
	while (sprite_array[i])
	{
		thrd_i = 0;
		while (thrd_i < MAX_THRD)
		{
			raycast[thrd_i].thread_chunk = sprite_array[i]->width / MAX_THRD;
			raycast[thrd_i].thread_sprite = sprite_array[i];
			raycast[thrd_i].thrd_i = thrd_i;
			thrd_i++;
		}
		init_threads(raycast, thread_sprite);
		i++;
	}
	free(sprite_array);
}

void	raycast(t_data *data)
{
	t_raycast	raycast[MAX_THRD];

	init_raycast(data, &data->player, raycast);
	init_threads(raycast, thread_raycast);
	if (data->sprite_list)
		handle_sprites(raycast);
}
