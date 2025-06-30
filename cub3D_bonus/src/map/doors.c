#include "cub3D.h"

static int	valid_door(char **map, int y, int x)
{
	int	valid;

	valid = 0;
	// Check vertical walls
	if (ft_strchr(WALLS, map[y - 1][x])
		&& ft_strchr(WALLS, map[y + 1][x]))
		valid = 1;
	// Check horizontal walls
	if (ft_strchr(WALLS, map[y][x - 1])
		&& ft_strchr(WALLS, map[y][x + 1]))
	{
		if (valid == 1)
			return (0);
		return (1);
	}
	if (valid == 1)
		return (1);
	return (0);
}
int	check_doors(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(DOORS, (map[i][j])))
			{
				if (!valid_door(map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
