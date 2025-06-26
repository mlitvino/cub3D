#include "cub3D.h"

void	replace_unit_points(t_data *data, int grid_x, int grid_y)
{
	int		y;
	int		max_y;
	char	new_char;

	if (ft_strchr(FLOORS, data->grid_map[grid_y - 1][grid_x]))
		new_char = data->grid_map[grid_y - 1][grid_x];
	else if (ft_strchr(FLOORS, data->grid_map[grid_y + 1][grid_x]))
		new_char = data->grid_map[grid_y + 1][grid_x];
	else if (ft_strchr(FLOORS, data->grid_map[grid_y][grid_x + 1]))
		new_char = data->grid_map[grid_y][grid_x + 1];
	else if (ft_strchr(FLOORS, data->grid_map[grid_y][grid_x - 1]))
		new_char = data->grid_map[grid_y][grid_x - 1];
	else
		new_char = EMPTY;
	y = grid_y * BLOCK_SIZE;
	max_y = y + BLOCK_SIZE;
	while (y < max_y)
	{
		ft_memset(&data->unit_map[y][grid_x * BLOCK_SIZE], new_char, BLOCK_SIZE);
		y++;
	}
}
