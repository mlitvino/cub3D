/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:53:55 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/01 16:07:40 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	no_path_return(t_sprite *sprite)
{
	if (sprite->path)
	{
		free_path(sprite->path);
		sprite->path = NULL;
	}
	sprite->path = NULL;
	return (0);
}

void	switch_img(t_sprite *sprite)
{
	if (sprite->cur_img == sprite->tex_imgs[WOLF_STAY])
		sprite->cur_img = sprite->tex_imgs[WOLF_WALK1];
	if (++sprite->move_rate >= 12)
	{
		sprite->move_rate = 0;
		if (sprite->cur_img == sprite->tex_imgs[WOLF_ATTCK])
			sprite->cur_img = sprite->tex_imgs[WOLF_WALK1];
		if (sprite->cur_img == sprite->tex_imgs[WOLF_WALK1])
			sprite->cur_img = sprite->tex_imgs[WOLF_WALK2];
		else if (sprite->cur_img == sprite->tex_imgs[WOLF_WALK2])
			sprite->cur_img = sprite->tex_imgs[WOLF_WALK1];
	}
}

void	set_new_pos(t_data *data, t_sprite *sprite, float new_x, float new_y)
{
	if (can_move_wall_enemy(sprite, new_x, sprite->pos.y, data)
		&& can_move_enemy_collision(sprite, new_x, sprite->pos.y, data))
		sprite->pos.x = new_x;
	if (can_move_wall_enemy(sprite, sprite->pos.x, new_y, data)
		&& can_move_enemy_collision(sprite, sprite->pos.x, new_y, data))
		sprite->pos.y = new_y;
}

void	check_end_of_path(t_sprite *sprite)
{
	t_path	*tmp;

	tmp = sprite->path;
	if ((sprite->pos.x == sprite->last_seen.x
			&& sprite->pos.y == sprite->last_seen.y))
		sprite->has_player_in_sight = 0;
	while (tmp)
	{
		if (!tmp->parent)
		{
			if (sprite->pos.x / BLOCK_SIZE == tmp->pos.x && sprite->pos.y
				/ BLOCK_SIZE == tmp->pos.y)
			{
				free_path(sprite->path);
				sprite->path = NULL;
				return ;
			}
		}
		tmp = tmp->parent;
	}
}
