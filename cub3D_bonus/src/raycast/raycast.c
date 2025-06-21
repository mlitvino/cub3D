/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:43:06 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/21 13:23:57 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	compre_dist(t_raycast *raycast, t_wall *hor_wall, t_wall *ver_wall)
{
	if (hor_wall->dist < ver_wall->dist)
	{
		select_tex(raycast, hor_wall, HORIZONT);
		render_col(raycast, hor_wall, hor_wall->dist, raycast->tex_indx);
	}
	else if (ver_wall->dist < hor_wall->dist)
	{
		select_tex(raycast, ver_wall, VERTICAL);
		render_col(raycast, ver_wall, ver_wall->dist, raycast->tex_indx);
	}
	else if (hor_wall->dist != INT_MAX
		&& raycast->unit_map[hor_wall->pos.y][hor_wall->pos.x - 1] == WALL
		&& raycast->unit_map[hor_wall->pos.y][hor_wall->pos.x + 1] == WALL)
	{
		select_tex(raycast, hor_wall, HORIZONT);
		render_col(raycast, hor_wall, hor_wall->dist, raycast->tex_indx);
	}
	else
	{
		select_tex(raycast, ver_wall, VERTICAL);
		render_col(raycast, ver_wall, ver_wall->dist, raycast->tex_indx);
	}
}

void	cast_ray(t_raycast *raycast)
{
	find_wall(raycast, &raycast->hor_wall, HORIZONT);
	find_wall(raycast, &raycast->ver_wall, VERTICAL);
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
	chck_facing_enemy(raycast, sprite_array, raycast->player);
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
