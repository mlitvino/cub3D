/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:54:01 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/01 16:26:05 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	attack_player(t_data *data, t_sprite *sprite)
{
	if (sprite->dist <= sprite->attack_range)
	{
		if (++sprite->attack_rate >= 50 || sprite->moved > 40)
		{
			if (sprite->attack_rate >= 50)
				sprite->attack_rate = 0;
			if (IsSoundPlaying(data->sound[S_WOLF_GROWL]) == false)
				PlaySound(data->sound[S_WOLF_GROWL]);
			if (sprite->cur_img == sprite->tex_imgs[WOLF_WALK1]
				|| sprite->cur_img == sprite->tex_imgs[WOLF_WALK2])
			{
				get_damage(data, NULL, &data->player);
				sprite->cur_img = sprite->tex_imgs[WOLF_ATTCK];
			}
			else if (sprite->cur_img == sprite->tex_imgs[WOLF_ATTCK])
				sprite->cur_img = sprite->tex_imgs[WOLF_WALK2];
			else if (sprite->cur_img == sprite->tex_imgs[WOLF_WALK2])
			{
				get_damage(data, NULL, &data->player);
				sprite->cur_img = sprite->tex_imgs[WOLF_ATTCK];
			}
		}
		return ;
	}
}

static void free_after_door(t_path *path)
{
	t_path *tmp;
	t_path *last;

	last = path;
	path = path->parent;
	while (path)
	{
		tmp = path->parent;
		free(path);
		path = tmp;
	}
	last->parent = NULL;
}

static int	truncate_path_if_closed_door(t_sprite *sprite, t_path *prev,
		t_path *tmp, t_data *data)
{
	t_door	*door;
	int		x;
	int		y;

	x = tmp->parent->pos.x;
	y = tmp->parent->pos.y;
	if (data->grid_map[y][x] == 'D')
	{
		door = find_door(data->door_list, x * BLOCK_SIZE, y * BLOCK_SIZE);
		if (door && door->state != OPEN)
		{
			if (prev)
			{
				free_after_door(tmp);
				return (1);
			}
			else
			{
				free_path(sprite->path);
				sprite->path = NULL;
				return (1);
			}
		}
	}
	return (0);
}

static void	check_closed_door_in_path(t_data *data, t_sprite *sprite)
{
	t_path	*tmp;
	t_path	*prev;

	prev = NULL;
	tmp = sprite->path;
	while (tmp && sprite->has_player_in_sight)
	{
		if (tmp->parent)
		{
			if (truncate_path_if_closed_door(sprite, prev, tmp, data))
				return ;
		}
		prev = tmp;
		tmp = tmp->parent;
	}
}

void	wolf_action(t_sprite *sprite, t_data *data)
{
	attack_player(data, sprite);
	if (has_line_of_sight(sprite, &data->player, data->unit_map)
		&& sprite->dist < MAX_WOLF_VIS * BLOCK_SIZE)
	{
		if (sprite->path)
		{
			free_path(sprite->path);
			sprite->path = NULL;
		}
		sprite->last_seen = data->player.pos;
		sprite->has_player_in_sight = 1;
		sprite->path = bfs_find_path(data, sprite->pos, data->player.pos);
		if (sprite->path)
			move_to_goal(sprite, data);
	}
	else if (sprite->has_player_in_sight)
	{
		check_closed_door_in_path(data, sprite);
		if (sprite->path)
			move_to_goal(sprite, data);
		else
			sprite->has_player_in_sight = 0;
	}
	else
		sprite->cur_img = sprite->tex_imgs[WOLF_STAY];
}
