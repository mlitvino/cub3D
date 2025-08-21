/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:24:23 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/02 13:18:02 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

static void	update_player_rotation(t_data *game, int delta_x)
{
	float	sensitivity;

	sensitivity = 0.03f;
	game->player.pov.view_angl -= delta_x * sensitivity;
	if (game->player.pov.view_angl >= 360)
		game->player.pov.view_angl -= 360;
	else if (game->player.pov.view_angl < 0)
		game->player.pov.view_angl += 360;
}

static void	update_camera_pitch(t_data *game, int delta_y)
{
	int	vertical_speed;

	vertical_speed = 1;
	game->plane.center.y -= (delta_y * vertical_speed) / 2;
	if (game->plane.center.y > WIN_H + 300)
		game->plane.center.y = WIN_H + 300;
	else if (game->plane.center.y < -400)
		game->plane.center.y = -400;
}

void	handle_mouse_rotation(t_data *game, int dx, int dy)
{
	update_player_rotation(game, dx);
	update_camera_pitch(game, dy);
}
