#include "cub3D.h"

static int	door_in_line_of_sight(double x, double y, t_data *data, char **map)
{
	t_door	*door;

	if (map[(int)y][(int)x] == 'D')
	{
		door = find_door(data->door_list, x, y);
		if (door && door->state != OPEN)
			return (1);
	}
	return (0);
}

int	has_line_of_sight(t_sprite *enemy, t_char *player, char **map)
{
	double	dx;
	double	dy;
	double	x;
	double	y;
	double	dist;

	x = enemy->pos.x;
	y = enemy->pos.y;
	dx = player->pos.x - enemy->pos.x;
	dy = player->pos.y - enemy->pos.y;
	dist = sqrt(dx * dx + dy * dy);
	enemy->dist_player = dist;
	while (dist > 0)
	{
		x += (dx / enemy->dist_player) * 0.5;
		y += (dy / enemy->dist_player) * 0.5;
		dist -= 0.5;
		if (map[(int)y][(int)x] == '1')
			return (0);
		if (door_in_line_of_sight(x, y, player->data, map))
			return (0);
	}
	return (1);
}
