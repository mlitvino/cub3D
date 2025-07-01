/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:04:13 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/01 15:06:29 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_char *player, double angle_offset)
{
	double	angle_rad;
	double	dx;
	double	dy;
	int		new_x;
	int		new_y;

	angle_rad = deg_rad(player->pov.view_angl + angle_offset);
	dx = cos(angle_rad) * player->move_spd;
	dy = -sin(angle_rad) * player->move_spd;
	new_x = player->pos.x + dx;
	new_y = player->pos.y + dy;
	if (!check_for_wall_collision(player, new_x, player->pos.y))
		player->pos.x += dx;
	if (!check_for_wall_collision(player, player->pos.x, new_y))
		player->pos.y += dy;
	if (IsMusicStreamPlaying(player->data->music[M_PLAYER_STEP]) == false)
		PlayMusicStream(player->data->music[M_PLAYER_STEP]);
}

static int	check_for_enemy_collision(t_char *player, double new_x,
		double new_y)
{
	t_sprite	*sprite;
	double		collision_distance;
	double		dx;
	double		dy;
	double		dist;

	sprite = player->data->sprite_list;
	while (sprite)
	{
		if (sprite->walkable == false)
		{
			dx = sprite->pos.x - new_x;
			dy = sprite->pos.y - new_y;
			dist = sqrt(dx * dx + dy * dy);
			collision_distance = sprite->hitbox_radius + player->hitbox_radius;
			if (dist < collision_distance)
				return (1);
		}
		sprite = sprite->next;
	}
	return (0);
}

int	check_for_wall_collision(t_char *player, double new_x, double new_y)
{
	if (!can_move_wall(player, new_x, new_y))
	{
		return (1);
	}
	if (!can_move_door(player, new_x, new_y))
	{
		return (1);
	}
	if (check_for_enemy_collision(player, new_x, new_y))
		return (1);
	return (0);
}
