/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:14:11 by ablodorn          #+#    #+#             */
/*   Updated: 2025/06/30 15:14:12 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**perror_return(void)
{
	perror("cub3D");
	return (NULL);
}

int	perror_return_int(int *data)
{
	perror("cub3D3");
	if (data)
		free(data);
	return (0);
}

char	**perror_free(char **map_data, int fd)
{
	perror("cub3D2");
	return (free_map(map_data, fd));
}

int	perror_exit(char *line)
{
	if (line)
		free(line);
	perror("cub3D");
	return (0);
}

char	*perror_exit_null(void)
{
	perror("cub3D");
	return (NULL);
}
