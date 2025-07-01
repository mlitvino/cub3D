/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:06:08 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/01 17:42:27 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	can_move_wall_enemy(t_sprite *sprite, float new_x, float new_y,
		t_data *data)
{
	int		cell_top;
	int		cell_bottom;
	int		cell_left;
	int		cell_right;
	char	**unit_map;

	unit_map = data->unit_map;
	cell_top = floor((new_y - (sprite->hitbox_radius / 4)));
	cell_bottom = floor((new_y + (sprite->hitbox_radius / 4)));
	cell_left = floor((new_x - (sprite->hitbox_radius / 4)));
	cell_right = floor((new_x + (sprite->hitbox_radius / 4)));
	if (cell_top < 0 || cell_left < 0 || cell_bottom >= data->map_h * BLOCK_SIZE
		|| cell_right >= data->map_w * BLOCK_SIZE)
	{
		return (0);
	}
	if (ft_strchr(WALLS, unit_map[cell_top][cell_left]) || ft_strchr(WALLS,
			unit_map[cell_top][cell_right]) || ft_strchr(WALLS,
			unit_map[cell_bottom][cell_left]) || ft_strchr(WALLS,
			unit_map[cell_bottom][cell_right]))
	{
		return (0);
	}
	return (1);
}

void	handle_img_set_pos(t_data *data, t_sprite *sprite,
		float new_x, float new_y)
{
	switch_img(sprite);
	set_new_pos(data, sprite, new_x, new_y);
	check_end_of_path(sprite);
}

static int	move_wolf(t_sprite *sprite, t_data *data, int x, int y)
{
	float	new_x;
	float	new_y;
	float	dx;
	float	dy;
	float	dist;

	dx = x - sprite->pos.x;
	dy = y - sprite->pos.y;
	dist = sqrtf(dx * dx + dy * dy);
	if (sprite->dist <= sprite->attack_range)
	{
		sprite->moved = 0;
		return (no_path_return(sprite));
	}
	else
	{
		if (IsSoundPlaying(data->sound[S_WOLF_CHASE]) == false)
			PlaySound(data->sound[S_WOLF_CHASE]);
		new_x = sprite->pos.x + sprite->move_spd * (dx / dist);
		new_y = sprite->pos.y + sprite->move_spd * (dy / dist);
		sprite->moved++;
		handle_img_set_pos(data, sprite, new_x, new_y);
	}
	return (1);
}

void	move_to_goal(t_sprite *sprite, t_data *data)
{
	t_path	*next_step;
	float	target_x;
	float	target_y;

	next_step = sprite->path;
	if (!sprite->path)
	{
		no_path(sprite);
		return ;
	}
	while (next_step->parent && !(next_step->parent->pos.x == (int)sprite->pos.x
			&& next_step->parent->pos.y == (int)sprite->pos.y))
	{
		next_step = next_step->parent;
	}
	target_x = next_step->pos.x * BLOCK_SIZE + BLOCK_SIZE / 2;
	target_y = next_step->pos.y * BLOCK_SIZE + BLOCK_SIZE / 2;
	if (!move_wolf(sprite, data, target_x, target_y))
	{
		return ;
	}
}
