/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:14:07 by ablodorn          #+#    #+#             */
/*   Updated: 2025/06/30 15:14:08 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	lines(int fd, char *buffer)
{
	ssize_t	bytes_read;
	int		i;
	int		count;

	count = 0;
	bytes_read = read(fd, buffer, 42);
	while (bytes_read > 0)
	{
		i = 0;
		while (i < bytes_read)
		{
			if (buffer[i] == '\n')
				count++;
			i++;
		}
		bytes_read = read(fd, buffer, 42);
	}
	if (bytes_read < 0)
	{
		perror("Error reading file");
		close(fd);
		exit(1);
	}
	return (count);
}

static int	count_lines(const char *filename)
{
	int		count;
	int		fd;
	char	buffer[42];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCould not open map file\n", 2);
		exit(1);
	}
	count = lines(fd, buffer);
	close(fd);
	return (count + 1);
}

static void	remove_newlines_empty_lines(char **lines, int line_count)
{
	int	i;
	int	len;
	int	count;

	if (!lines)
		return ;
	count = line_count - 1;
	if (!lines[count])
		count--;
	while (is_empty_line(lines[count]))
	{
		free(lines[count]);
		lines[count] = NULL;
		count--;
	}
	i = 0;
	while (lines[i])
	{
		len = ft_strlen(lines[i]);
		if (len > 0 && lines[i][len - 1] == '\n')
			lines[i][len - 1] = '\0';
		i++;
	}
}

int	last_line_no_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	**read_file(char *filename, t_data *data)
{
	char	**map_data;
	int		fd;

	if (!valid_extension(filename))
		return (error_return("Error\nInvalid file extension\n"));
	data->line_count = count_lines(filename);
	if (data->line_count < 9)
		return (error_return("Error\nInvalid file content\n"));
	map_data = ft_calloc((data->line_count) + 1, sizeof(char *));
	if (!map_data)
		return (perror_return());
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror_return());
	if (!fill_map(data, map_data, fd))
		return (perror_free(map_data, fd));
	remove_newlines_empty_lines(map_data, data->line_count);
	close(fd);
	return (map_data);
}
