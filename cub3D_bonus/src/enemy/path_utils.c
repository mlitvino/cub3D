#include "cub3D.h"

int	init_visited(int ***visited, t_data *data)
{
	int i;
	int j;

	i = 0;
	*visited = malloc(data->map_h * sizeof(int *));
	if (!(*visited))
	{
		perror("cub3D");
   		return (0);
	}
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
    }
	return (1);
}

void	init_delta(int dx[4], int dy[4])
{
	dx[0] = 1;
	dx[1] = -1;
	dx[2] = 0;
	dx[3] = 0;
	dy[0] = 0;
	dy[1] = 0;
	dy[2] = 1;
	dy[3] = -1;
}

t_path	*create_node(int x, int y, t_path *parent)
{
	t_path *node;

	node = malloc(sizeof(t_path));
	if (!node)
		return (NULL);
	node->pos.x = x;
	node->pos.y = y;
	node->parent = parent;
	return (node);
}

void free_queue_except_path(t_path **queue, int front, int rear, t_path *path_end)
{
	t_path *node;
	t_path *p;
	int on_path;
	int i ;

    i = front;
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

int	has_line_of_sight(t_sprite *enemy, t_player *player, char **map)
{
	double	dx;
	double	dy;
	double	x;
	double	y;
	double	dist;

	x = enemy->pos.x;
	y = enemy->pos.y;
	dx = player->pos.x - enemy->pos.x;
	dy = player->pos.y - enemy->pos.y;
	dist = sqrt(dx * dx + dy * dy);
	enemy->dist_player = dist;
	while (dist > 0)
	{
		x += (dx / enemy->dist_player) * 0.05;
		y += (dy / enemy->dist_player) * 0.05;
		dist -= 0.05;
		if (map[(int)y][(int)x] == '1') // Wall hit
			return (0);
		i++;
	}
	return (1);
}