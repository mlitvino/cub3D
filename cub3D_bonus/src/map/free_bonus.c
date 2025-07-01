/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:14:29 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/01 17:42:27 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
