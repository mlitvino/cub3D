/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wall_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:24:42 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/29 17:05:07 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_on_map(t_data *data, t_point *p)
{
	return ((0 <= p->x && p->x < data->map_w * BLOCK_SIZE) && (0 <= p->y
			&& p->y < data->map_h * BLOCK_SIZE));
}

bool	is_hit(char **unit_map, t_point *wall)
{
	if (unit_map[wall->y][wall->x] == WALL)
		return (true);
	return (false);
}
