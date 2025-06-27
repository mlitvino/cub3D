#include "cub3D.h"

static int	is_valid_tile(char **map, t_data *data, int x, int y)
{
	t_door *door;
	t_sprite *sprite;

	if (x < 0 || y < 0 || x >= data->map_w || y >= data->map_h)
    	return (0);
	if (map[y][x] == '1')
    	return (0);
	if (map[y][x] == 'D')
	{
		door = find_door(data->door_list, x * BLOCK_SIZE, y * BLOCK_SIZE);
		if (!door || door->state != OPEN)
			return (0);
	}
	return (1);
}


static int	bfs_explore_neighbors(t_data *data, t_bfs *bfs, t_delta *d, t_path *current)
{
	int	i;
	int nx;
	int ny;

	i = 0;
	while (i < 4)
	{
		nx = current->pos.x + d->dx[i];
		ny = current->pos.y + d->dy[i];
		if (is_valid_tile(data->grid_map, data, nx, ny) && !bfs->visited[ny][nx])
		{
			bfs->visited[ny][nx] = 1;
			bfs->queue[bfs->rear++] = create_node(nx, ny, current);
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
		free_queue_except_path(bfs->queue, bfs->front, bfs->rear, current);
		return (1);
	}
	return (0);
}

static t_path	*bfs_loop(t_data *data, t_bfs *bfs, t_delta *d, t_point goal)
{
	t_path	*current;
	int i;

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

void free_visited(int **visited, int height)
{
	int i;

	i = 0;
	while (i < height && visited[i])
		free(visited[i++]);
	free(visited);
}

t_path	*bfs_find_path(t_data *data, t_point start, t_dpoint goal)
{
	t_bfs		bfs;
	t_delta		d;
	t_point		s;
	t_point		g;
	t_path		*result;

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
	int count = 0;
	t_path	*tmp = result;
	while (result)
	{
		count++;
		result = result->parent;
	}
	result = tmp;
	if (count == 1)
	{
		free(result);
		return (NULL);
	}
	free_visited(bfs.visited, data->map_h);
	return (result);
}
