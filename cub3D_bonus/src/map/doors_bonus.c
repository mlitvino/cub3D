/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:14:40 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/01 17:42:27 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	valid_door(char **map, int y, int x)
{
	int	valid;

	valid = 0;
	if (ft_strchr(WALLS, map[y - 1][x])
		&& ft_strchr(WALLS, map[y + 1][x]))
		valid = 1;
	if (ft_strchr(WALLS, map[y][x - 1])
		&& ft_strchr(WALLS, map[y][x + 1]))
	{
		if (valid == 1)
			return (0);
		return (1);
	}
	if (valid == 1)
		return (1);
	return (0);
}

int	check_doors(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(DOORS, (map[i][j])))
			{
				if (!valid_door(map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
