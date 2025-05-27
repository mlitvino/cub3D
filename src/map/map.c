#include "cub3D.h"

int valid_map(t_data *data, char *file)
{
	char **padded_map;

	padded_map = pad_map(data->grid_map, data->map_h);
	if (!valid_extension(file))
	{
		printf("Error\n Invalid map extension\n");
		return (0);
	}
	if (!valid_player_count(data->grid_map, data))
	{
		printf("Error\n Invalid player count\n");
		return (0);
	}
	if (!valid_characters(data->grid_map))
	{
		printf("Error\n Invalid character found inside the map\n");
		return (0);
	}
	if (!check_map_borders(data->grid_map, data->map_h) || is_valid_surrounding(padded_map, data->map_h, data->map_w))
	{
		printf("Error\n Map not surrounded by walls\n");
		return (0);
	}
	return (1);
}

// check characters and file extension
int	valid_player_count(char **map, t_data *data)
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
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
			{
				player_count++;
				data->player->pos.x = i;
				data->player->pos.x = j;
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

int	valid_characters(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr("01NSWE ", map[i][j])) //can add extra characters for bonus
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

// pad the map with "P"

static int	longest_line(char **map, int height)
{
	int i;
	int max_len;
	int	len;

	max_len = 0;
	i = 0;
	while(i < height)
	{
		len = ft_strlen(map[i]);
		if (len > max_len)
            max_len = len;
		i++;
	}
	return (max_len);
}

char **pad_map(char **map, int height)
{
	char	**padded_map;
	int		line_len;
	int		max_len;
	int		i;
	int		j;

	padded_map = malloc(sizeof(char *) * (height + 1));
    if (!padded_map)
        return (NULL);
	max_len = longest_line(map, height);
	i = 0;
	while (i < height)
	{
		line_len = ft_strlen(map[i]);
		padded_map[i] = malloc(sizeof(char) * (max_len + 1));
		if (!padded_map[i])
		{
			while(i > 0)
				free(padded_map[--i]);
			free(padded_map);
			return (NULL);
		}
		ft_strcpy(padded_map[i], map[i]);
		j = line_len;
		while (j < max_len)
			padded_map[i][j] = 'P';
		padded_map[i][max_len] = '\0';
		i++;
	}
	padded_map[height] = NULL;
    return padded_map;
}

// map borders

int check_map_borders(char **map, int height)
{
    int i;
    int len;

    if (height < 3)
        return (0);
	//Check first row
    len = ft_strlen(map[0]);
    i = 0;
    while (i < len)
    {
        if (map[0][i] != '1' && map[0][i] != ' ')
            return (0);
        i++;
    }
	//Check last row
    len = ft_strlen(map[height - 1]);
    i = 0;
    while (i < len)
    {
        if (map[height - 1][i] != '1' && map[height - 1][i] != ' ')
            return (0);
        i++;
    }
    // Check middle rows: first and last character must be '1'
    i = 1;
    while (i < height - 1)
    {
        len = strlen(map[i]);
        if (len < 3)
            return (0);
        if (map[i][0] != '1')
            return (0);
        if (map[i][len - 1] != '1')
            return (0);
        i++;
	}
    return (1);
}


static int is_walkable(char c)
{
    return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int is_allowed_adjacent(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int is_valid_surrounding(char **map, int height, int width)
{
    int row;
    int col;
    int delta_row;
    int delta_col;
    char neighbor;

    row = 0;
    while (row < height)
    {
        col = 0;
        while (col < width)
        {
            if (is_walkable(map[row][col]))
            {
                delta_row = -1;
                while (delta_row <= 1)
                {
                    delta_col = -1;
                    while (delta_col <= 1)
                    {
                        if (!(delta_row == 0 && delta_col == 0))
                        {
                            neighbor = map[row + delta_row][col + delta_col];
                            if (!is_allowed_adjacent(neighbor))
                                return (0);
                        }
                        delta_col++;
                    }
                    delta_row++;
                }
            }
            col++;
        }
        row++;
    }
    return (1);
}
