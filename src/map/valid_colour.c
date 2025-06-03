#include "cub3D.h"

static int	valid_colour_number(char *colour, int floor_ceiling, int rgb, t_data *data)
{
	int colour_atoi;

	colour_atoi = ft_atoi(colour);
	if (colour_atoi > 255 || colour_atoi < 0)
		return (0);
	if (floor_ceiling)
	{
		if (rgb == 1)
			data->flor_rgb.r = colour_atoi;
		else if (rgb == 2)
			data->flor_rgb.g = colour_atoi;
		else if (rgb == 3)
			data->flor_rgb.b = colour_atoi;
	}
	if (!floor_ceiling)
	{
		if (rgb == 1)
			data->ceil_rgb.r = colour_atoi;
		else if (rgb == 2)
			data->ceil_rgb.g = colour_atoi;
		else if (rgb == 3)
			data->ceil_rgb.b = colour_atoi;
	}
	return (1);
}


int valid_colours(t_data *data)
{
	if (!valid_colour_number(data->mlx_data.ceiling_colour[0], 0, 1, data) || !valid_colour_number(data->mlx_data.ceiling_colour[1], 0, 2, data) || !valid_colour_number(data->mlx_data.ceiling_colour[2], 0, 3, data))
	{
		ft_putstr_fd("Error\nInvalid ceiling colour detected\n", 2);
		return (0);
	}
	if (!valid_colour_number(data->mlx_data.floor_colour[0], 1, 1, data) || !valid_colour_number(data->mlx_data.floor_colour[1], 1, 2, data) || !valid_colour_number(data->mlx_data.floor_colour[2], 1, 3, data))
	{
		ft_putstr_fd("Error\nInvalid floor colour detected\n", 2);
		return (0);
	}
	return (1);
}

char *set_colour(t_data *data, char *line, int *i, int done)
{
	char *colour;
	int	j;
	int	k;

	k = 0;
	colour = malloc(sizeof(char) * 4);
	if (!colour)
		perror_exit(data);
	j = (*i);
	while (line[(*i)] && (*i) < j + 3 && line[*i] != ',')
	{
		if (!ft_isdigit(line[(*i)]))
			error_exit(data, "Error\nInvalid colour format\n");
		colour[k++] = line[(*i)];
		(*i)++;
	}
	colour[k] = '\0';
	if (done && ft_strlen(colour) == 0)
		error_exit(data, "Error\nInvalid colour format\n");
	if (line[(*i)] && done)
		error_exit(data, "Error\nInvalid colour format\n");
	if (((!line[(*i)]) && !done) || (line[(*i)] && line[(*i)] != ','))
		error_exit(data, "Error\nInvalid colour format\n");
	if (line[(*i)] && line[(*i)] == ',')
		(*i)++;
	return (colour);
}

void set_floor_ceiling(t_data *data, char *element, char *line)
{
	int i;
	char *line_trim;

	i = 0;
	if (!ft_strcmp(element, "F "))
	{
		data->mlx_data.floor_colour = malloc(sizeof(char *) * 4);
		line_trim = ft_strtrim(line + 1, " \n");
		if (!line_trim || !data->mlx_data.floor_colour)
			perror_exit(data);
		data->mlx_data.floor_colour[0] = set_colour(data, line_trim , &i, 0);
		data->mlx_data.floor_colour[1] = set_colour(data, line_trim , &i, 0);
		data->mlx_data.floor_colour[2] = set_colour(data, line_trim , &i, 1);
		data->mlx_data.floor_colour[3] = NULL;
	}
	if (!ft_strcmp(element, "C "))
	{
		data->mlx_data.ceiling_colour = malloc(sizeof(char *) * 4);
		line_trim = ft_strtrim(line + 1, " \n");
		if (!line_trim || !data->mlx_data.ceiling_colour)
			perror_exit(data);
		data->mlx_data.ceiling_colour[0] = set_colour(data, line_trim , &i, 0);
		data->mlx_data.ceiling_colour[1] = set_colour(data, line_trim , &i, 0);
		data->mlx_data.ceiling_colour[2] = set_colour(data, line_trim , &i, 1);
		data->mlx_data.ceiling_colour[3] = NULL;
	}
}
