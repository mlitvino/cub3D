#include "cub3D.h"

// check characters and file extension
static int	valid_player_count(char **map, t_data *data)
{
	int	player_count;
	int	i;
	int	j;

	player_count = 0;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				player_count++;
				set_angle(map[i][j], data);
				data->player.pos.y = i * BLOCK_SIZE + (BLOCK_SIZE / 2);
				data->player.pos.x = j * BLOCK_SIZE + (BLOCK_SIZE / 2);
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (0);
	else
		return (1);
}

static int	valid_characters(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr("01NSWEDBCF ", map[i][j]))
				// can add extra characters for bonus
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

// pad the map with "P"

int	longest_line(char **map, int height)
{
	int	i;
	int	max_len;
	int	len;

	max_len = 0;
	i = 0;
	while (i < height)
	{
		len = ft_strlen(map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
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
		// j = line_len;
		while (j < data->map_w)
			padded_map[i][j++] = 'P';
		padded_map[i][data->map_w] = '\0';
		i++;
	}
	padded_map[height] = NULL;
	return (1);
}

// map borders

int	valid_map(t_data *data)
{
	data->grid_map = pad_map(data->work_map, data->map_h, data);
	if (!data->grid_map)
		return (0);
	if (!valid_player_count(data->work_map, data))
		return (error_free_return("Error\nInvalid player count\n", data));
	if (!valid_characters(data->work_map))
		return (error_free_return("Error\nInvalid character found inside the map\n",
				data));
	if (!check_map_borders(data->work_map, data->map_h))
		return (error_free_return("Error\nMap not surrounded by walls and/or invalid space inside the map\n",
				data));
	if (!is_valid_surrounding(data->grid_map, data->map_h, data->map_w))
		return (error_free_return("Error\nMap not surrounded by walls and/or invalid space inside the map\n",
				data));
	if (!check_doors(data->work_map))
		return (error_free_return("Error\nInvalid door detected\n", data));
	free_map(data->work_map, -1);
	return (1);
}
