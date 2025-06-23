#include "cub3D.h"

int	valid_end_of_string(int *i, int done, char *line, char *colour)
{
	while (line[*i] == ' ')
		(*i)++;
	if ((done && line[*i] != '\0') || (!done && line[*i] != ','))
		return (free_error_exit(line, colour));
	if (done && ft_strlen(colour) == 0)
		return (free_error_exit(line, colour));
	if (line[(*i)] && done)
		return (free_error_exit(line, colour));
	if (((!line[(*i)]) && !done) || (line[(*i)] && line[(*i)] != ','))
		return (free_error_exit(line, colour));
	if (line[(*i)] && line[(*i)] == ',')
		(*i)++;
	return (1);
}

int	valid_colour_number(char *colour, int floor_ceiling, int rgb, t_data *data)
{
	int	colour_atoi;

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

int	valid_colours(t_data *data)
{
	if (!valid_colour_number(data->mlx_data.ceiling_colour[0], 0, 1, data)
		|| !valid_colour_number(data->mlx_data.ceiling_colour[1], 0, 2, data)
		|| !valid_colour_number(data->mlx_data.ceiling_colour[2], 0, 3, data))
	{
		ft_putstr_fd("Error\nInvalid ceiling colour detected\n", 2);
		return (0);
	}
	if (!valid_colour_number(data->mlx_data.floor_colour[0], 1, 1, data)
		|| !valid_colour_number(data->mlx_data.floor_colour[1], 1, 2, data)
		|| !valid_colour_number(data->mlx_data.floor_colour[2], 1, 3, data))
	{
		ft_putstr_fd("Error\nInvalid floor colour detected\n", 2);
		return (0);
	}
	return (1);
}

char	*set_colour(char *line, int *i, int done)
{
	char	*colour;
	int		j;
	int		k;

	k = 0;
	colour = malloc(sizeof(char) * 4);
	if (!colour)
		return (perror_exit_null());
	while (line[(*i)] && line[*i] == ' ')
		(*i)++;
	j = (*i);
	while (line[(*i)] && (*i) < (j + 3) && line[*i] != ',' && line[*i] != ' ')
	{
		if (!ft_isdigit(line[(*i)]))
		{
			free_error_exit(line, colour);
			return (NULL);
		}
		colour[k++] = line[(*i)++];
	}
	colour[k] = '\0';
	if (!valid_end_of_string(i, done, line, colour))
		return (NULL);
	return (colour);
}

int	set_rgb(int floor_or_ceiling, char *line_trim, int *i, t_data *data)
{
	if (floor_or_ceiling)
	{
		if (!set_floor_colour(data, line_trim, i))
			return (0);
		return (1);
	}
	else
	{
		if (!set_ceiling_colour(data, line_trim, i))
			return (0);
		return (1);
	}
}