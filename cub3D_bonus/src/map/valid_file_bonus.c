/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:13:58 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/01 17:42:27 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

int	is_valid_data(char **map, t_data *data, int line_count)
{
	int	i;

	i = 0;
	data->work_map = malloc(sizeof(char *) * (line_count - i + 1));
	if (!data->work_map)
		return (perror_return_int(NULL));
	if (!create_temp_map(map, &i, data))
		return (free_return(NULL));
	while (map[i] != NULL && is_empty_line(map[i]))
		i++;
	if (map[i])
	{
		return (free_map_return(data));
	}
	return (1);
}
