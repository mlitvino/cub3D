/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:12:16 by ablodorn          #+#    #+#             */
/*   Updated: 2025/06/30 16:25:23 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	open_closed_door(t_char *player, double x, double y)
{
	t_door	*door;

	door = find_door(player->data->door_list, x, y);
	if (door && door->state != OPEN)
		return (0);
	else
		return (1);
}

int	can_move_door(t_char *player, double new_x, double new_y)
{
	int		cell_top;
	int		cell_bottom;
	int		cell_left;
	int		cell_right;
	char	**unit_map;

	unit_map = player->data->unit_map;
	cell_top = floor((new_y - player->hitbox_radius));
	cell_bottom = floor((new_y + player->hitbox_radius));
	cell_left = floor((new_x - player->hitbox_radius));
	cell_right = floor((new_x + player->hitbox_radius));
	if (cell_top < 0 || cell_left < 0 || cell_bottom >= player->data->map_h
		* BLOCK_SIZE || cell_right >= player->data->map_w * BLOCK_SIZE)
	{
		return (0);
	}
	if (ft_strchr(DOORS, unit_map[cell_top][cell_left]) || ft_strchr(DOORS,
			unit_map[cell_top][cell_right]) || ft_strchr(DOORS,
			unit_map[cell_bottom][cell_left]) || ft_strchr(DOORS,
			unit_map[cell_bottom][cell_right]))
	{
		return (open_closed_door(player, new_x, new_y));
	}
	return (1);
}

int	can_move_wall(t_char *player, double new_x, double new_y)
{
	int		cell_top;
	int		cell_bottom;
	int		cell_left;
	int		cell_right;
	char	**unit_map;

	unit_map = player->data->unit_map;
	cell_top = floor((new_y - player->hitbox_radius));
	cell_bottom = floor((new_y + player->hitbox_radius));
	cell_left = floor((new_x - player->hitbox_radius));
	cell_right = floor((new_x + player->hitbox_radius));
	if (cell_top < 0 || cell_left < 0 || cell_bottom >= player->data->map_h
		* BLOCK_SIZE || cell_right >= player->data->map_w * BLOCK_SIZE)
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
