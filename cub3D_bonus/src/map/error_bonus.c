/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:14:36 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/01 17:42:27 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	return_invalid_element(void)
{
	ft_putstr_fd("Error\nInvalid or missing map element\n", 2);
	return (0);
}

int	error_exit(char *message)
{
	ft_putstr_fd(message, 2);
	return (0);
}

char	**error_return(char *message)
{
	ft_putstr_fd(message, 2);
	return (NULL);
}

int	free_return(int *data)
{
	if (data)
		free(data);
	return (0);
}

int	perror_free_map(char **map)
{
	perror("cub3D");
	free_map(map, -1);
	return (0);
}
