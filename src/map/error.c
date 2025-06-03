#include "cub3D.h"

int	return_invalid_element(int i)
{
	ft_putstr_fd("Error\nInvalid or missing map element\n", 2);
	printf("i: %d\n", i);
	return (0);
}

void	perror_exit(t_data *data)
{
	if (data->mlx_data.tex_path[NORTH])
		free(data->mlx_data.tex_path[NORTH]);
	if (data->mlx_data.tex_path[WEST])
		free(data->mlx_data.tex_path[WEST]);
	if (data->mlx_data.tex_path[SOUTH])
		free(data->mlx_data.tex_path[SOUTH]);
	if (data->mlx_data.tex_path[EAST])
		free(data->mlx_data.tex_path[EAST]);
	if (data->mlx_data.ceiling_colour)
		free(data->mlx_data.ceiling_colour);
	if (data->mlx_data.floor_colour)
		free(data->mlx_data.ceiling_colour);
	free_map(data->map_data, -1);
	perror("cub3D 5:");
	exit (1);
}

void	error_exit(t_data *data, char * message)
{
	if (data->mlx_data.tex_path[NORTH])
		free(data->mlx_data.tex_path[NORTH]);
	if (data->mlx_data.tex_path[SOUTH])
		free(data->mlx_data.tex_path[SOUTH]);
	if (data->mlx_data.tex_path[WEST])
		free(data->mlx_data.tex_path[WEST]);
	if (data->mlx_data.tex_path[EAST])
		free(data->mlx_data.tex_path[EAST]);
	if (data->mlx_data.floor_colour)
		free(data->mlx_data.floor_colour);
	if (data->mlx_data.ceiling_colour)
		free(data->mlx_data.ceiling_colour);
	free_map(data->map_data, -1);
	ft_putstr_fd(message, 2);
	exit (1);
}