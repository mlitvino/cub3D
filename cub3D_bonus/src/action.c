/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:42:45 by mlitvino          #+#    #+#             */
/*   Updated: 2025/07/01 15:42:57 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_damage(t_data *data, t_sprite *spr, t_char *player)
{
	if (spr && spr->type == WOLF)
	{
		if (--spr->hp <= 0)
		{
			spr->cur_img = spr->tex_imgs[WOLF_DEAD];
			spr->state = WOLF_DEAD;
			spr->walkable = true;
		}
	}
	else
	{
		if (--player->hp <= 0)
		{
			change_game_state(data, DEATH);
		}
	}
}

void	shoot(t_data *data, t_char *player)
{
	t_sprite	*enemy;

	if (player->ammo > 0 && player->is_shooting == 0
		&& IsSoundPlaying(data->sound[S_SHOT]) == false)
	{
		enemy = player->facing_enemy;
		player->ammo--;
		player->is_shooting = true;
		if (enemy)
		{
			get_damage(data, enemy, player);
		}
		PlaySound(data->sound[S_SHOT]);
		data->mlx_data.textrs_img[CROSSBOW1]->enabled = false;
		data->mlx_data.textrs_img[CROSSBOW2]->enabled = true;
	}
}
