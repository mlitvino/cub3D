#include "cub3D.h"

int is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

char	**free_map(char **map, int fd)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
			free(map[i++]);
		free(map);
	}
	if (fd >= 0)
		close(fd);
	return (NULL);
}


void	free_colours_textures_strings(t_data *data)
{
	free(data->mlx_data.tex_path[WEST]);
	free(data->mlx_data.tex_path[NORTH]);
	free(data->mlx_data.tex_path[EAST]);
	free(data->mlx_data.tex_path[SOUTH]);
	free(data->mlx_data.ceiling_colour);
	free(data->mlx_data.floor_colour);
}

void	init_null(t_data *data)
{
	data->mlx_data.tex_path[WEST] = NULL;
	data->mlx_data.tex_path[NORTH] = NULL;
	data->mlx_data.tex_path[EAST] = NULL;
	data->mlx_data.tex_path[SOUTH] = NULL;
	data->mlx_data.ceiling_colour = NULL;
	data->mlx_data.floor_colour = NULL;
}