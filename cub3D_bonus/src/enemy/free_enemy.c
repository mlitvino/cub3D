#include "cub3D.h"

void	free_path(t_path *path)
{
	t_path	*next;

	while (path)
	{
		next = path->parent;
		free(path);
		path = next;
	}
}

void	free_queue_except_path(t_path **queue, int front, int rear,
		t_path *path_end)
{
	t_path	*node;
	t_path	*p;
	int		on_path;
	int		i;

	i = front;
	while (i < rear)
	{
		node = queue[i];
		p = path_end;
		on_path = 0;
		while (p)
		{
			if (p == node)
			{
				on_path = 1;
				break ;
			}
			p = p->parent;
		}
		if (!on_path)
			free(node);
		i++;
	}
}

void	free_visited(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height && visited[i])
		free(visited[i++]);
	free(visited);
}

void	no_path(t_sprite *sprite)
{
	if (sprite->path)
	{
		free_path(sprite->path);
		sprite->path = NULL;
	}
}

void	free_paths(t_sprite *sprites)
{
	while (sprites)
	{
		if (sprites->path)
			free_path(sprites->path);
		sprites = sprites->next;
	}
}
