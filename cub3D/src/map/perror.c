#include "cub3D.h"

char	**perror_return(void)
{
	perror("cub3D1");
	return (NULL);
}

int	perror_return_int(int *data)
{
	perror("cub3D3");
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
