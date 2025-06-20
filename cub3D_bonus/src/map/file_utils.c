#include "cub3D.h"

int	free_element_map(int *element, t_data *data)
{
	free(element);
	return (free_map_return(data));
}

int	create_temp_map(char **map, int *i, t_data *data)
{
	int	j;

	j = 0;
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

int	is_identifier(char *line)
{
	int	identifier;

	identifier = 0;
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "WE ", 3))
		identifier = 1;
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		identifier = 1;
	return (identifier);
}

int	is_map_element(char *line, int *map_element, t_data *data)
{
	if (!is_identifier(line))
		return (return_invalid_element());
	if (!check_double_element_wall(&map_element[0], "NO ", line, data))
		return (0);
	if (!check_double_element_wall(&map_element[1], "SO ", line, data))
		return (0);
	if (!check_double_element_wall(&map_element[2], "WE ", line, data))
		return (0);
	if (!check_double_element_wall(&map_element[3], "EA ", line, data))
		return (0);
	if (!check_double_element_wall(&map_element[4], "F ", line, data))
		return (0);
	if (!check_double_element_wall(&map_element[5], "C ", line, data))
		return (0);
	return (1);
}
