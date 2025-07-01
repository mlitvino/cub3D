/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:53:52 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/01 13:52:34 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	bfs_explore_neighbors(t_data *data, t_bfs *bfs, t_delta *d,
		t_path *current)
{
	int	i;
	int	nx;
	int	ny;
	t_path *node;

	i = 0;
	while (i < 4)
	{
		nx = current->pos.x + d->dx[i];
		ny = current->pos.y + d->dy[i];
		if (is_valid_tile(data->grid_map, data, nx, ny)
			&& !bfs->visited[ny][nx])
		{
			bfs->visited[ny][nx] = 1;
			node = create_node(nx, ny, current);
			if (!node)
				return (0);
			bfs->queue[bfs->rear++] = node;
			if (bfs->rear >= 150)
				return (0);
		}
		i++;
	}
	return (1);
}

static int	bfs_check_goal(t_path *current, t_bfs *bfs, t_point goal)
{
	if (current->pos.x == goal.x && current->pos.y == goal.y)
	{
		free_queue_except_path(bfs->queue, bfs->rear, current);
		return (1);
	}
	return (0);
}

static t_path	*bfs_loop(t_data *data, t_bfs *bfs, t_delta *d, t_point goal)
{
	t_path	*current;
	int		i;

	while (bfs->front < bfs->rear)
	{
		current = bfs->queue[bfs->front++];
		if (bfs_check_goal(current, bfs, goal))
		{
			current = reverse_path(current);
			return (current);
		}
		if (!bfs_explore_neighbors(data, bfs, d, current))
			break ;
	}
	i = 0;
	while (i < bfs->rear)
		free(bfs->queue[i++]);
	return (NULL);
}

t_path	*bfs_find_path(t_data *data, t_point start, t_dpoint goal)
{
	t_bfs	bfs;
	t_delta	d;
	t_point	s;
	t_point	g;
	t_path	*result;

	s.x = start.x / BLOCK_SIZE;
	s.y = start.y / BLOCK_SIZE;
	g.x = goal.x / BLOCK_SIZE;
	g.y = goal.y / BLOCK_SIZE;
	bfs.front = 0;
	bfs.rear = 0;
	if (!init_visited(&bfs.visited, data))
		return (NULL);
	init_delta_path(&d);
	bfs.queue[bfs.rear++] = create_node(s.x, s.y, NULL);
	bfs.visited[s.y][s.x] = 1;
	result = bfs_loop(data, &bfs, &d, g);
	free_visited(bfs.visited, data->map_h);
	return (result);
}
