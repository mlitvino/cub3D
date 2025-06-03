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

static int	valid_extension(const char *filename)
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
static void	remove_newlines(char **lines)
{
	int		i;
	int		len;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		len = ft_strlen(lines[i]);
		if (len > 0 && lines[i][len - 1] == '\n')
			lines[i][len - 1] = '\0';
		i++;
	}
}

char **read_file(char *filename, t_data *data)
{
	char	**map_data;
	int		i;
	int		fd;
	char *	line;

	i = 0;
	if (!valid_extension(filename))
	{
		ft_putstr_fd("Error\nInvalid map extension\n", 2);
		return (NULL);
	}
	data->line_count = count_lines(filename);
	if (data->line_count < 9)
	{
		ft_putstr_fd("Error\nInvalid file content\n", 2);
		return (NULL);
	}
	map_data = ft_calloc((data->line_count) + 1, sizeof(char *));
	if (!map_data)
	{
		return (NULL);
		perror("cub3D 1");
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("cub3D 2");
		return (NULL);
	}
	line = get_next_line(fd);
	if (!line)
	{
		perror("cub3D 3");
		return (free_map(map_data, fd));
	}
	//printf("line_coutn: %d\n", data->line_count); ///////////////////////
	while (line != NULL)
	{
		map_data[i++] = line;
		line = get_next_line(fd);
		if (!line && i < data->line_count)
		{
			perror("cub3D 4");
			return (free_map(map_data, fd));
		}
	}
	map_data[i] = NULL;
	remove_newlines(map_data);
	close(fd);
	return (map_data);
}
