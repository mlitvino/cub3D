/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:59:10 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/02 13:04:02 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	set_wall_image(t_data *data, char *element, char *line)
{
	if (!ft_strcmp(element, "NO "))
	{
		data->mlx_data.tex_path[NORTH] = ft_strtrim(line + 2, " 	");
		if (!data->mlx_data.tex_path[NORTH])
			return (perror_exit(NULL));
	}
	else if (!ft_strcmp(element, "SO "))
	{
		data->mlx_data.tex_path[SOUTH] = ft_strtrim(line + 2, " 	");
		if (!data->mlx_data.tex_path[SOUTH])
			return (perror_exit(NULL));
	}
	else if (!ft_strcmp(element, "WE "))
	{
		data->mlx_data.tex_path[WEST] = ft_strtrim(line + 2, " 	");
		if (!data->mlx_data.tex_path[WEST])
			return (perror_exit(NULL));
	}
	else if (!ft_strcmp(element, "EA "))
	{
		data->mlx_data.tex_path[EAST] = ft_strtrim(line + 2, " 	");
		if (!data->mlx_data.tex_path[EAST])
			return (perror_exit(NULL));
	}
	return (1);
}

int	check_double_element_wall(int *map_element, char *element, char *line,
		t_data *data)
{
	int	length;

	length = ft_strlen(element);
	if (!ft_strncmp(element, line, length))
	{
		if (*map_element != 0)
			return (return_invalid_element());
		if (length == 2)
		{
			if (!set_floor_ceiling(data, element, line))
				return (0);
		}
		else if (length == 3)
		{
			if (!set_wall_image(data, element, line))
				return (0);
		}
		*map_element = 1;
	}
	return (1);
}

static int	found_all_elements(int *map_elements)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (map_elements[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

static int	find_map_elements(char **map, int *map_element, t_data *data,
		int *i)
{
	int	j;

	while (map[*i] != NULL)
	{
		j = 0;
		if (is_empty_line(map[*i]))
		{
			(*i)++;
			continue ;
		}
		if (*i > 5 && found_all_elements(map_element))
			break ;
		while (map[*i][j] && map[*i][j] == ' ')
			j++;
		if (!is_map_element(map[*i] + j, map_element, data))
			return (0);
		(*i)++;
	}
	return (1);
}

int	is_valid_data(char **map, t_data *data, int line_count)
{
	int	i;
	int	*map_element;

	i = 0;
	map_element = malloc(sizeof(int) * 6);
	if (!map_element)
		return (perror_return_int(map_element));
	ft_bzero(map_element, sizeof(int) * 6);
	if (!find_map_elements(map, map_element, data, &i))
		return (free_return(map_element));
	if (!valid_colours(data))
		return (free_return(map_element));
	data->work_map = malloc(sizeof(char *) * (line_count - i + 1));
	if (!data->work_map)
		return (perror_return_int(map_element));
	if (!create_temp_map(map, &i, data))
		return (free_return(map_element));
	while (map[i] != NULL && is_empty_line(map[i]))
		i++;
	if (map[i])
		return (free_element_map(map_element, data));
	free(map_element);
	return (1);
}
