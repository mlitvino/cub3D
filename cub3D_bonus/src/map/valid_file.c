#include "cub3D.h"

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
