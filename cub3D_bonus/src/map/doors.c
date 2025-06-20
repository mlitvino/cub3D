#include "cub3D.h"

static int valid_door(char **map, int y, int x)
{
	int	valid;

	valid = 0;
	// Check vertical walls
    if (map[y - 1][x] == '1' && map[y + 1][x] == '1')
        valid = 1;
    // Check horizontal walls
    if (map[y][x - 1] == '1' && map[y][x + 1] == '1')
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
	int i;
	int j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D')
			{
				if (!valid_door(map, i , j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}






