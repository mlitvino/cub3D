/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:53:47 by ablodorn          #+#    #+#             */
/*   Updated: 2025/06/30 14:53:48 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_visited(int ***visited, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	*visited = malloc(data->map_h * sizeof(int *));
	if (!(*visited))
		return (perror_return_int(NULL));
	while (i < data->map_h)
	{
		(*visited)[i] = malloc(data->map_w * sizeof(int));
		if (!(*visited)[i])
		{
			while (--i >= 0)
				free((*visited)[i]);
			free((*visited));
			perror("cub3D");
			return (0);
		}
		j = 0;
		while (j < data->map_w)
			(*visited)[i][j++] = 0;
		i++;
	}
	return (1);
}

void	init_delta_path(t_delta *d)
{
	d->dx[0] = 1;
	d->dx[1] = -1;
	d->dx[2] = 0;
	d->dx[3] = 0;
	d->dy[0] = 0;
	d->dy[1] = 0;
	d->dy[2] = 1;
	d->dy[3] = -1;
}

t_path	*create_node(int x, int y, t_path *parent)
{
	t_path	*node;

	node = malloc(sizeof(t_path));
	if (!node)
		return (NULL);
	node->pos.x = x;
	node->pos.y = y;
	node->parent = parent;
	return (node);
}

t_path	*reverse_path(t_path *end)
{
	t_path	*prev;
	t_path	*current;
	t_path	*next;

	prev = NULL;
	current = end;
	while (current)
	{
		next = current->parent;
		current->parent = prev;
		prev = current;
		current = next;
	}
	return (prev);
}

int	is_valid_tile(char **map, t_data *data, int x, int y)
{
	t_door		*door;
	t_sprite	*sprite;

	if (x < 0 || y < 0 || x >= data->map_w || y >= data->map_h)
		return (0);
	if (ft_strchr(WALLS, map[y][x]))
		return (0);
	if (ft_strchr(DOORS, map[y][x]))
	{
		door = find_door(data->door_list, x * BLOCK_SIZE, y * BLOCK_SIZE);
		if (!door || door->state != OPEN)
			return (0);
	}
	return (1);
}
