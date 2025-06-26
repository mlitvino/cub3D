#include "cub3D.h"

static int	is_valid_tile(char **map, t_data *data, int x, int y)
{
	t_door *door;

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


/*t_path	*bfs_find_path(char **map, t_data *data, t_point start, t_point goal)
{
	int				**visited;
	t_path		*queue[10000];
	int				front;
	int				rear;
	t_path		*current;
	int				dx[4];
	int				dy[4];
	int nx;
	int ny;

	start.x /= BLOCK_SIZE;
	start.y /= BLOCK_SIZE;
	goal.x /= BLOCK_SIZE;
	goal.y /= BLOCK_SIZE;
	rear = 0;
	front = 0;

	if (!init_visited(&visited, data))
		return (NULL); //might need to exit here cleanup before
	init_delta(dx, dy);
	queue[rear++] = create_node(start.x, start.y, NULL);
	visited[start.y][start.x] = 1;
	while (front < rear)
	{
		current = queue[front++];
		if (current->pos.x == goal.x && current->pos.y == goal.y)
		{
			free_queue_except_path(queue, front, rear, current);
			return (current); 
		}
		for (int i = 0; i < 4; i++)
		{
			nx = current->pos.x + dx[i];
			ny = current->pos.y + dy[i];
			if (is_valid_tile(map, data, nx, ny) && !visited[ny][nx])
			{
				visited[ny][nx] = 1;
				queue[rear++] = create_node(nx, ny, current);
				if (rear >= 10000)
					break ;
			}
		}
	}
	for (int i = front; i < rear; i++)
    	free(queue[i]);
	return (NULL); // No path found
}*/

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

/*static int	bfs_explore_neighbors(t_data *data, t_bfs *bfs, t_delta *d, t_path *current)
{
	int	i;
	int	nx;
	int	ny;

	i = 0;
	while (i < 4)
	{
		nx = current->pos.x + d->dx[i];
		ny = current->pos.y + d->dy[i];

		// Check map bounds, walls, and visited status
		if (is_valid_tile(data->grid_map, data, nx, ny) && !bfs->visited[ny][nx])
		{
			// Check if another enemy already occupies this tile
			t_sprite *enemy = data->sprite_list;
			int	occupied = 0;
			while (enemy)
			{
				if (enemy->type == WOLF) // or your enemy type
				{
					int ex = (int)(enemy->pos.x / BLOCK_SIZE);
					int ey = (int)(enemy->pos.y / BLOCK_SIZE);
					if (ex == nx && ey == ny)
					{
						occupied = 1;
						break;
					}
				}
				enemy = enemy->next;
			}
			if (occupied)
			{
				i++;
				continue;
			}

			// Mark as visited and enqueue the node
			bfs->visited[ny][nx] = 1;
			bfs->queue[bfs->rear++] = create_node(nx, ny, current);
			if (bfs->rear >= 150)
				return (0);
		}
		i++;
	}
	return (1);
}*/

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

t_path	*bfs_find_path(t_data *data, t_point start, t_dpoint goal)
{
	t_bfs		bfs;
	t_delta		d;
	t_point		s;
	t_point		g;

	s.x = start.x / BLOCK_SIZE;
	s.y = start.y / BLOCK_SIZE;
	g.x = goal.x / BLOCK_SIZE;
	g.y = goal.y / BLOCK_SIZE;
	bfs.front = 0;
	bfs.rear = 0;

	//printf("BFS: start=(%d,%d), goal=(%d,%d)\n", s.x, s.y, g.x, g.y);

	if (!init_visited(&bfs.visited, data))
		return (NULL);
	init_delta_path(&d);

	bfs.queue[bfs.rear++] = create_node(s.x, s.y, NULL);
	bfs.visited[s.y][s.x] = 1;

	return (bfs_loop(data, &bfs, &d, g));
}
