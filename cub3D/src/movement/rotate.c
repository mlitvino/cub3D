/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:59:19 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/01 14:59:20 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_player_right(t_char *player)
{
	player->pov.view_angl += player->turn_spd;
	if (player->pov.view_angl >= 360)
		player->pov.view_angl -= 360;
}

void	rotate_player_left(t_char *player)
{
	player->pov.view_angl -= player->turn_spd;
	if (player->pov.view_angl < 0)
		player->pov.view_angl += 360;
}
