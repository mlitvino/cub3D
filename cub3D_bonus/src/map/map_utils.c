#include "cub3D.h"

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

int	fill_map(t_data *data, char **map_data, int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line != NULL)
	{
		map_data[i++] = line;
		line = get_next_line(fd);
		if (!line && i < data->line_count && !last_line_no_newline(map_data[i
				- 1]))
			return (0);
	}
	map_data[i] = NULL;
	return (1);
}

int	valid_extension(const char *filename)
{
	int			len;
	const char	*extension;

	extension = ".cub";
	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + (len - 4), extension, 4))
		return (0);
	return (1);
}

char	**pad_map(char **map, int height, t_data *data)
{
	char	**padded_map;

	padded_map = malloc(sizeof(char *) * (height + 1));
	if (!padded_map)
		return (NULL);
	data->map_w = longest_line(map, height);
	if (data->map_w > 1000)
	{
		free(padded_map);
		ft_putstr_fd("Error\nMap is too big\n", 2);
		return (NULL);
	}
	if (!fill_padded_map(height, data, padded_map, map))
		return (NULL);
	return (padded_map);
}

void	set_angle(char angle, t_data *data)
{
	if (angle == 'N')
		data->player.pov.view_angl = 90;
	if (angle == 'S')
		data->player.pov.view_angl = 270;
	if (angle == 'W')
		data->player.pov.view_angl = 180;
	if (angle == 'E')
		data->player.pov.view_angl = 0;
}