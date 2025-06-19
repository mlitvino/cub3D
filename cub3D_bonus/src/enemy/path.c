#include "cub3D.h"

int	has_line_of_sight(t_sprite *enemy, t_player *player, char **map)
{
	double	dx;
	double	dy;
	int		i;
	double	x;
	double	y;

	x = enemy->pos.x;
	y = enemy->pos.y;
	dx = player->pos.x - enemy->pos.x;
	dy = player->pos.y - enemy->pos.y;
	enemy->dist_player = sqrt(dx * dx + dy * dy);
	i = 0;
	while (i < (int)enemy->dist_player)
	{
		x += (dx / enemy->dist_player);
		y += (dy / enemy->dist_player);
		if (map[(int)y][(int)x] == '1') // Wall hit
			return (0);
		i++;
	}
	return (1);
}

t_path	*create_node(int x, int y, t_path *parent)
{
	t_path *node = malloc(sizeof(t_path));
	if (!node)
		return (NULL);
	node->pos.x = x;
	node->pos.y = y;
	node->parent = parent;
	return (node);
}

int	is_valid_tile(char **map, t_data *data, int x, int y)
{
	t_door *door;

	if (x < 0 || y < 0 || x >= data->map_w || y >= data->map_h)
    	return (0);
	if (map[y][x] == '1')
    	return (0);
	if (map[y][x] != 'D')
		door = find_door(data->door_list, x * BLOCK_SIZE, y * BLOCK_SIZE);
	if (!door || door->state != OPEN)
		return (0);
	return (1);
}

void free_queue_except_path(t_path **queue, int front, int rear, t_path *path_end)
{
	t_path *node;
	t_path *p;
	int on_path;

    int i = front;
    while (i < rear)
    {
        node = queue[i];
        p = path_end;
        on_path = 0;

        // Walk backward from path_end to see if node is on the path
        while (p)
        {
            if (p == node)
            {
                on_path = 1;
                break;
            }
            p = p->parent;
        }
        if (!on_path)
            free(node);
        i++;
    }
}

t_path	*bfs_find_path(char **map, t_data *data, t_point start, t_point goal)
{
	int				visited[data->map_h][data->map_w] = {{0}};
	t_path		*queue[1000];
	int				front = 0;
	int				rear = 0;
	t_path		*current;
	int				dx[4] = {1, -1, 0, 0};
	int				dy[4] = {0, 0, 1, -1};
	int nx;
	int ny;

	start.x /= BLOCK_SIZE;
	start.y /= BLOCK_SIZE;
	goal.x /= BLOCK_SIZE;
	goal.y /= BLOCK_SIZE;
	
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
				if (rear >= 1000)
					break ;
			}
		}
	}
	for (int i = front; i < rear; i++)
    	free(queue[i]);
	return (NULL); // No path found
}