#include "cub3D.h"

int	set_floor_colour(t_data *data, char *line_trim, int *i)
{
	data->mlx_data.floor_colour[0] = set_colour(line_trim, i, 0);
	if (!data->mlx_data.floor_colour[0])
		return (0);
	data->mlx_data.floor_colour[1] = set_colour(line_trim, i, 0);
	if (!data->mlx_data.floor_colour[1])
		return (0);
	data->mlx_data.floor_colour[2] = set_colour(line_trim, i, 1);
	if (!data->mlx_data.floor_colour[2])
		return (0);
	data->mlx_data.floor_colour[3] = NULL;
	return (1);
}

int	set_ceiling_colour(t_data *data, char *line_trim, int *i)
{
	data->mlx_data.ceiling_colour[0] = set_colour(line_trim, i, 0);
	if (!data->mlx_data.ceiling_colour[0])
		return (0);
	data->mlx_data.ceiling_colour[1] = set_colour(line_trim, i, 0);
	if (!data->mlx_data.ceiling_colour[1])
		return (0);
	data->mlx_data.ceiling_colour[2] = set_colour(line_trim, i, 1);
	if (!data->mlx_data.ceiling_colour[2])
		return (0);
	data->mlx_data.ceiling_colour[3] = NULL;
	return (1);
}

static int	set_floor(t_data *data, char *line)
{
	char	*line_trim;
	int		j;
	int		i;

	i = 0;
	j = 0;
	data->mlx_data.floor_colour = malloc(sizeof(char *) * 4);
	line_trim = ft_strtrim(line + 1, " 	");
	if (!line_trim || !data->mlx_data.floor_colour)
		return (perror_exit(line_trim));
	while (j < 4)
		data->mlx_data.floor_colour[j++] = NULL;
	if (!set_rgb(1, line_trim, &i, data))
		return (0);
	free(line_trim);
	return (1);
}

static int	set_ceiling(t_data *data, char *line)
{
	char	*line_trim;
	int		j;
	int		i;

	i = 0;
	j = 0;
	data->mlx_data.ceiling_colour = malloc(sizeof(char *) * 4);
	line_trim = ft_strtrim(line + 1, " 	");
	if (!line_trim || !data->mlx_data.ceiling_colour)
		return (perror_exit(line_trim));
	while (j < 4)
		data->mlx_data.ceiling_colour[j++] = NULL;
	if (!set_rgb(0, line_trim, &i, data))
		return (0);
	free(line_trim);
	return (1);
}

int	set_floor_ceiling(t_data *data, char *element, char *line)
{
	if (!ft_strcmp(element, "F "))
	{
		if (!set_floor(data, line))
			return (0);
		return (1);
	}
	if (!ft_strcmp(element, "C "))
	{
		if (!set_ceiling(data, line))
			return (0);
		return (1);
	}
	return (1);
}
