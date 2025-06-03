#include "cub3D.h"


// check characters and file extension
static int	valid_player_count(char **map)
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
				//data->player.pos.x = i;
				//data->player.pos.x = j;
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

static char **pad_map(char **map, int height, t_data *data)
{
	char	**padded_map;
	int		line_len;
	int		i = 0;
	int		j;

	//while (map[i])
		//printf("%s\n", map[i++]);
	padded_map = malloc(sizeof(char *) * (height));
	if (!padded_map)
	{
    	return (NULL);
	}
	data->map_w = longest_line(map, height);
	i = 0;
	while (i < height)
	{
		line_len = ft_strlen(map[i]);
		padded_map[i] = malloc(sizeof(char) * (data->map_w + 1));
		if (!padded_map[i])
		{
			while(i > 0)
				free(padded_map[--i]);
			free(padded_map);
			return (NULL);
		}
		padded_map[i] = ft_strdup(map[i]);
		if (!padded_map[i])
		{
			while(i > 0)
				free(padded_map[--i]);
			free(padded_map);
			return (NULL);
		}
		j = line_len;
		while (j < data->map_w)
			padded_map[i][j++] = 'P';
		padded_map[i][data->map_w] = '\0';
		i++;
	}
	padded_map[height] = NULL;
    return (padded_map);
}

// map borders
static int check_map_borders(char **map, int height)
{
    int i;
    int len;
	int j;

    if (height < 3)
        return (0);
	//Check first row
    len = ft_strlen(map[0]);
    i = 0;
    while (i < len)
    {
        if (map[0][i] != '1' && map[0][i] != ' ')
		{
			printf("1\n");
            return (0);
		}
        i++;
    }
	//Check last row
    len = ft_strlen(map[height - 1]);
    i = 0;
    while (i < len)
    {
        if (map[height - 1][i] != '1' && map[height - 1][i] != ' ')
		{
			printf("2\n");
            return (0);
		}
        i++;
    }
    // Check middle rows: first and last character must be '1'
    i = 1;
    while (i < height - 1)
    {
		j = 0;
        len = ft_strlen(map[i]);
        if (len < 3)
        {
			printf("3\n");
            return (0);
		}
		while(map[i][j] == ' ')
			j++;
        if (map[i][j] != '1')
        {
			printf("4\n");
            return (0);
		}
        if (map[i][len - 1] != '1')
		{
			printf("5\n");
            return (0);
		}
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

static int	error_free_return(char *message, t_data *data)
{
	ft_putstr_fd(message, 2);
	free_map(data->grid_map, -1);
	return (0);
}

int valid_map(t_data *data)
{
	int i = 0;
	while(data->work_map[i])
		printf("%s\n", data->work_map[i++]);
	data->grid_map = pad_map(data->work_map, data->map_h, data);
	if (!data->grid_map)
	{
		perror("cub3D 6:");
		return (0);
	}
	if (!valid_player_count(data->work_map))
		return (error_free_return("Error\nInvalid player count\n", data));
	if (!valid_characters(data->work_map))
		return (error_free_return("Error\nInvalid character found inside the map\n", data));
	if (!check_map_borders(data->work_map, data->map_h))
		return (error_free_return("Error\nMap not surrounded by walls and/or invalid space inside the map\n", data));
	if (!is_valid_surrounding(data->work_map, data->map_h, data->map_w))
		return (error_free_return("Error\nMap not surrounded by walls and/or invalid space inside the map\n", data));
	free(data->work_map);
	return (1);
}
