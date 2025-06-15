/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:43:06 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/15 12:12:14 by mlitvino         ###   ########.fr       */
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

void	chck_facing_enemy(t_raycast *raycast, t_sprite **sprite_array, t_char *player)
{
	int	i;

	i = 0;
	player->facing_statue = NULL;
	player->facing_enemy = NULL;
	while (sprite_array && sprite_array[i])
		i++;
	i--;

	int WID = 6;
	while (i >= 0)
	{
		if (!player->facing_enemy && (sprite_array[i]->type == WOLF || sprite_array[i]->type == STATUE)
			&& raycast->data->rays_dist[raycast->scr_img->width / 2] > sprite_array[i]->dist
			&& sprite_array[i]->left < raycast->scr_img->width / 2
			&& raycast->scr_img->width / 2 < sprite_array[i]->left + sprite_array[i]->width
			&& sprite_array[i]->top < raycast->scr_img->height / 2
			&& raycast->scr_img->height / 2 < sprite_array[i]->top + sprite_array[i]->height)
		{
			player->facing_enemy = sprite_array[i];
		}
		if (!player->facing_statue && sprite_array[i]->type == STATUE)
		{
			if (sprite_array[i]->dist < STATUE_MAX_VIS * BLOCK_SIZE)
			{
				if	(!(sprite_array[i]->size.x + sprite_array[i]->width / WID < 0
					|| sprite_array[i]->size.x - sprite_array[i]->width / WID >= raycast->scr_img->width)
					&& !(sprite_array[i]->size.y + sprite_array[i]->height / 3 < 0
					|| sprite_array[i]->size.y - sprite_array[i]->height / 3 >= raycast->scr_img->height)
				)
					player->facing_statue = sprite_array[i];
			}
		}
		i--;
	}
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
