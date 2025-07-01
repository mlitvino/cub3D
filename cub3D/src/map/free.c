/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:58:42 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/01 14:58:43 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**free_map(char **map, int fd)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
			free(map[i++]);
		free(map);
	}
	if (fd >= 0)
		close(fd);
	return (NULL);
}

void	free_colours_textures_strings(t_data *data)
{
	free(data->mlx_data.tex_path[WEST]);
	free(data->mlx_data.tex_path[NORTH]);
	free(data->mlx_data.tex_path[EAST]);
	free(data->mlx_data.tex_path[SOUTH]);
	free_map(data->mlx_data.ceiling_colour, -1);
	free_map(data->mlx_data.floor_colour, -1);
}

int	error_free_return(char *message, t_data *data)
{
	ft_putstr_fd(message, 2);
	free_map(data->grid_map, -1);
	return (0);
}

int	free_map_return(t_data *data)
{
	free_map(data->work_map, -1);
	ft_putstr_fd("Error\nInvalid map data\n", 2);
	return (0);
}

int	free_error_exit(char *line, char *colour)
{
	free(line);
	free(colour);
	return (error_exit("Error\nInvalid colour format\n"));
}
