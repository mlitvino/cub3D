#include "cub3D.h"

static int	check_first_row(char **map)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(map[0]);
	while (i < len)
	{
		if (map[0][i] != '1' && map[0][i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	check_last_row(char **map, int height)
{
	int		i;
	int		len;

	len = ft_strlen(map[height - 1]);
	i = 0;
	while (i < len)
	{
		if (map[height - 1][i] != '1' && map[height - 1][i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	check_middle_rows(char **map, int height)
{
	int	i;
	int	len;
	int	j;

	i = 1;
	while (i < height - 1)
	{
		j = 0;
		len = ft_strlen(map[i]);
		if (len < 3)
			return (0);
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] != '1')
			return (0);
		if (map[i][len - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_map_borders(char **map, int height)
{
	if (height < 3)
		return (0);
	if (!check_first_row(map))
		return (0);
	if (!check_last_row(map, height))
		return (0);
	if (!check_middle_rows(map, height))
		return (0);
	return (1);
}

int	fill_padded_map(int height, t_data *data, char **padded_map, char **map)
{
	int	i;
	int	j;
	int	line_len;

	i = 0;
	while (i < height)
	{
		line_len = ft_strlen(map[i]);
		padded_map[i] = malloc(sizeof(char) * (data->map_w + 1));
		if (!padded_map[i])
			return (perror_free_map(padded_map));
		j = 0;
		while (j < line_len)
		{
			padded_map[i][j] = map[i][j];
			j++;
		}
		while (j < data->map_w)
			padded_map[i][j++] = 'P';
		padded_map[i][data->map_w] = '\0';
		i++;
	}
	padded_map[height] = NULL;
	return (1);
}
