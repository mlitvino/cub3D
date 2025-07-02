/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   face_enemy_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:19:33 by mlitvino          #+#    #+#             */
/*   Updated: 2025/07/02 13:18:18 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	check_screen_center(t_raycast *raycast,
		t_sprite *sprite, t_point center)
{
	int	wall_dist;

	wall_dist = raycast->data->rays_dist[center.x];
	if (!raycast->player->facing_enemy
		&& (sprite->type == WOLF || sprite->type == STATUE
			|| sprite->type == TREE)
		&& sprite->dist < wall_dist
		&& sprite->left < center.x && center.x < sprite->left + sprite->width
		&& sprite->top < center.y && center.y < sprite->top + sprite->height)
	{
		raycast->player->facing_enemy = sprite;
	}
}

void	check_statue_look(t_raycast *raycast, t_sprite *sprite, t_point center)
{
	t_point	scr_size;
	int		left;
	int		top;

	scr_size.x = (int)raycast->scr_img->width;
	scr_size.y = (int)raycast->scr_img->height;
	left = sprite->size.x - sprite->width / W_STATUE_VIS_DEC;
	top = sprite->size.y - sprite->height / H_STATUE_VIS_DEC;
	if (!raycast->player->facing_statue && sprite->type == STATUE
		&& sprite->dist < STATUE_MAX_VIS * BLOCK_SIZE
		&& sprite->size.x < raycast->data->rays_dist[center.x]
		&& (!(sprite->size.x + sprite->width / W_STATUE_VIS_DEC < 0
				|| left >= scr_size.x)
			&& !(sprite->size.y + sprite->height / H_STATUE_VIS_DEC < 0
				|| top >= scr_size.y)))
	{
		raycast->player->facing_statue = sprite;
	}
}

void	chck_facing_enemy(t_raycast *raycast, t_sprite **sprite_array,
		t_char *player)
{
	int		i;
	t_point	center;

	center.x = raycast->scr_img->width / 2;
	center.y = raycast->scr_img->height / 2;
	player->facing_statue = NULL;
	player->facing_enemy = NULL;
	i = 0;
	while (sprite_array && sprite_array[i])
		i++;
	i--;
	while (i >= 0)
	{
		check_screen_center(raycast, sprite_array[i], center);
		check_statue_look(raycast, sprite_array[i], center);
		i--;
	}
}
