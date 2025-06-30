/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:14:33 by ablodorn          #+#    #+#             */
/*   Updated: 2025/06/30 15:45:48 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	skip_empty_lines(char **map, int *i)
{
	while (is_empty_line(map[(*i)]))
		(*i)++;
}

int	create_temp_map(char **map, int *i, t_data *data)
{
	int	j;

	j = 0;
	skip_empty_lines(map, i);
	while (map[(*i)] != NULL && !is_empty_line(map[(*i)]))
	{
		data->work_map[j] = ft_strdup(map[(*i)]);
		if (!data->work_map[j])
		{
			perror("cub3D:");
			free_map(data->work_map, -1);
			return (0);
		}
		(*i)++;
		j++;
	}
	data->map_h = j;
	data->work_map[j] = NULL;
	if (j > 1000)
	{
		free_map(data->work_map, -1);
		ft_putstr_fd("Error\nMap has too many lines\n", 2);
		return (0);
	}
	return (1);
}
