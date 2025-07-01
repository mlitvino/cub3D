/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:58:50 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/01 14:58:51 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	init_null(t_data *data)
{
	data->mlx_data.tex_path[WEST] = NULL;
	data->mlx_data.tex_path[NORTH] = NULL;
	data->mlx_data.tex_path[EAST] = NULL;
	data->mlx_data.tex_path[SOUTH] = NULL;
	data->mlx_data.ceiling_colour = NULL;
	data->mlx_data.floor_colour = NULL;
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
		if (!line && i < data->line_count
			&& !last_line_no_newline(map_data[i - 1]))
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
