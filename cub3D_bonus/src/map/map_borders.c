#include "cub3D.h"

static int	check_first_row(char **map)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(map[0]);
	while (i < len)
	{
		if (!ft_strchr(WALLS, map[0][i]) && map[0][i] != ' ')
		{
			printf("1\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_last_row(char **map, int height)
{
	int	i;
	int	len;

	len = ft_strlen(map[height - 1]);
	i = 0;
	while (i < len)
	{
		if (!ft_strchr(WALLS,map[height - 1][i]) && map[height - 1][i] != ' ')
		{
			printf("2\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_middle_rows(char **map, int height)
{
	int	i;
	int	len;
	int	j;

	i = 1;
	while (i < height - 1)
	{
		j = 0;
		len = ft_strlen(map[i]);
		if (len < 3)
			return (0);
		while (map[i][j] == ' ')
			j++;
		if (!ft_strchr(WALLS, map[i][j]))
			return (0);
		if (!ft_strchr(WALLS, map[i][len - 1]))
			return (0);
		i++;
	}
	return (1);
}
int	check_map_borders(char **map, int height)
{
	if (height < 3)
		return (0);
	if (!check_first_row(map))
		return (0);
	if (!check_last_row(map, height))
		return (0);
	if (!check_middle_rows(map, height))
		return (0);
	return (1);
}
