#include "cub3D.h"

int	create_temp_map(char **map, int *i, t_data *data)
{
	int	j;

	j = 0;
	while (is_empty_line(map[(*i)]))
		(*i)++;
	while (map[(*i)] != NULL && !is_empty_line(map[(*i)]))
	{
		data->work_map[j] = ft_strdup(map[(*i)]);
		if (!data->work_map[j])
		{
			perror("cub3D:");
			free_map(data->work_map, -1);
			return (0);
		}
		(*i)++;
		j++;
	}
	data->map_h = j;
	data->work_map[j] = NULL;
	if (j > 1000)
	{
		free_map(data->work_map, -1);
		ft_putstr_fd("Error\nMap has too many lines\n", 2);
		return (0);
	}
	return (1);
}


