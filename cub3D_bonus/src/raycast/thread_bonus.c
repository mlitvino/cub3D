/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:16:05 by mlitvino          #+#    #+#             */
/*   Updated: 2025/07/01 17:42:27 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	*thread_sprite(void *arg)
{
	t_raycast	*raycast;
	t_sprite	*sprite;

	raycast = (t_raycast *)arg;
	sprite = raycast->thread_sprite;
	draw_sprite(raycast, sprite);
	return (NULL);
}

void	*thread_raycast(void *arg)
{
	t_raycast	*raycast;
	int			cur_ray;
	int			end_ray;

	raycast = (t_raycast *)arg;
	cur_ray = raycast->thread_chunk * raycast->thrd_i;
	end_ray = cur_ray + raycast->thread_chunk;
	if (raycast->thrd_i != MAX_THRD - 1)
		end_ray++;
	while (cur_ray < end_ray)
	{
		fill_ray_info(raycast);
		cast_ray(raycast);
		cur_ray++;
		raycast->ray_angle -= raycast->data->rays_angle;
		if (raycast->ray_angle < 0)
			raycast->ray_angle = 360 + raycast->ray_angle;
		raycast->cur_ray = cur_ray;
	}
	return (NULL);
}

void	init_threads(t_raycast *raycast, void *(routine)(void *arg))
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (i < MAX_THRD)
	{
		raycast[i].thrd_i = i;
		err |= pthread_create(&raycast[i].threads[i], NULL, routine,
				(void *)&raycast[i]);
		i++;
	}
	i = 0;
	while (i < MAX_THRD)
	{
		pthread_join(raycast[i].threads[i], NULL);
		i++;
	}
	if (err)
		clean_all(raycast->data, "pthread_create");
}
