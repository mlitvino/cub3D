#include "cub3D.h"

static void set_wall_image(t_data *data, char *element, char *line)
{
	if (!ft_strcmp(element, "NO "))
	{
		data->mlx_data.tex_path[NORTH] = ft_strtrim(line + 2, " \n");
		if (!data->mlx_data.tex_path[NORTH])
			perror_exit(data);
	}
	else if (!ft_strcmp(element, "SO "))
	{
		data->mlx_data.tex_path[SOUTH] = ft_strtrim(line + 2, " \n");
		if (!data->mlx_data.tex_path[SOUTH])
			perror_exit(data);
	}
	else if (!ft_strcmp(element, "WE "))
	{
		data->mlx_data.tex_path[WEST]  = ft_strtrim(line + 2, " \n");
		if (!data->mlx_data.tex_path[WEST])
			perror_exit(data);
	}
	else if (!ft_strcmp(element, "EA "))
	{
		data->mlx_data.tex_path[EAST] = ft_strtrim(line + 2, " \n");
		if (!data->mlx_data.tex_path[EAST])
			perror_exit(data);
	}
}

static int check_double_element_wall(int *map_element, char *element, char *line, t_data *data)
{
	int	length;

	length = ft_strlen(element);
	if (!ft_strncmp(element, line, length))
	{
		if (length == 2)
			set_floor_ceiling(data, element, line);
		else if (length == 3)
			set_wall_image(data, element, line);
		if (*map_element != 0)
			return (0);
		else
		{
			*map_element = 1;
			return (1);
		}
	}
	return (1);
}

static int	is_identifier(char *line)
{
	int identifier;

	identifier = 0;
	//printf("%s", line);
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "WE ", 3))
		identifier = 1;
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		identifier = 1;
	return (identifier);
}

static int	is_map_element(char *line, int *map_element, t_data *data)
{
	//int i = 0;
	//while(i < 6)
		//printf("%d\n",map_element[i++]);
	//printf("%s", line);
	if (!is_identifier(line))
		return (return_invalid_element(0));
	//printf("line: %s", line);
	if (!check_double_element_wall(&map_element[0], "NO ", line, data))
		return (return_invalid_element(1));
	if (!check_double_element_wall(&map_element[1], "SO ", line, data))
		return (return_invalid_element(2));
	if (!check_double_element_wall(&map_element[2], "WE ", line, data))
		return (return_invalid_element(3));
	if (!check_double_element_wall(&map_element[3], "EA ", line, data))
		return (return_invalid_element(4));
	if (!check_double_element_wall(&map_element[4], "F ", line, data))
		return (return_invalid_element(5));
	if (!check_double_element_wall(&map_element[5], "C ", line, data))
		return (return_invalid_element(6));
	return (1);
}

static int		found_all_elements(int *map_elements)
{
	int i;

	i = 0;
	while (i < 6)
	{
		if (map_elements[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_data(char **map, t_data *data, int line_count)
{
	int	i;
	int *map_element;
	int j;
	//int	found_all;

	//found_all = 0;
	map_element = malloc(sizeof(int) * 6);
	if (!map_element)
		return (0);
	ft_bzero(map_element, sizeof(int) * 6);
	i = 0;
	while(map[i] != NULL /*&& !found_all*/)
	{
		j = 0;
		if (is_empty_line(map[i]))
		{
			i++;
			continue ;
		}
		if (i > 5 && found_all_elements(map_element))
			break ;
		while(map[i][j] && map[i][j] == ' ')
			j++;
		if (!is_map_element(map[i] + j, map_element, data))
			return (0);
		i++;
	}
	if (!valid_colours(data))
		return (0);
	//while (map[i] && is_empty_line(map[i]))
		//i++;
	data->work_map = malloc(sizeof(char *) * (line_count - i + 1));
	if (!data->work_map )
	{
		perror("cub3D:");
		return (0);
	}
	j = 0;
	while (map[i] != NULL && !is_empty_line(map[i]))
	{
		data->work_map[j] = ft_strdup(map[i]);
		if(!data->work_map[j])
		{
			perror("cub3D:");
			free_map(data->work_map , - 1);
			return (0);
		}
		i++;
		j++;
	}
	data->map_h = j;
	data->work_map[j] = NULL;
	while (map[i] != NULL && is_empty_line(map[i]))
		i++;
	if (map[i])
	{
		printf("%s\n", map[i]);
		free_map(data->work_map , -1);
		ft_putstr_fd("Error\nInvalid map data\n", 2);
		return (0);
	}
	return (1);
}
