#include "cub3D.h"

void	move_player(t_char *player, double angle_offset)
{
	double	angle_rad;
	double	dx;
	double	dy;
	int		new_x;
	int		new_y;

	angle_rad = DEG_TO_RAD(player->pov.view_angl + angle_offset);
	dx = cos(angle_rad) * player->move_spd;
	dy = -sin(angle_rad) * player->move_spd;
	new_x = player->pos.x + dx;
	new_y = player->pos.y + dy;
	if (!check_for_wall_collision(player, new_x, player->pos.y))
		player->pos.x += dx;
	if (!check_for_wall_collision(player, player->pos.x, new_y))
		player->pos.y += dy;
	if (IsMusicStreamPlaying(player->data->music[M_PLAYER_STEP]) == false)
		PlayMusicStream(player->data->music[M_PLAYER_STEP]);
}

int	can_move_wall(t_char *player, double new_x, double new_y)
{
	int		cell_top;
	int		cell_bottom;
	int		cell_left;
	int		cell_right;
	char	**unit_map;

	unit_map = player->data->unit_map;
	cell_top = floor((new_y - player->hitbox_radius));
	cell_bottom = floor((new_y + player->hitbox_radius));
	cell_left = floor((new_x - player->hitbox_radius));
	cell_right = floor((new_x + player->hitbox_radius));
	if (cell_top < 0 || cell_left < 0 || cell_bottom >= player->data->map_h
		* BLOCK_SIZE || cell_right >= player->data->map_w * BLOCK_SIZE)
	{
		return (0);
	}
	if (unit_map[cell_top][cell_left] == WALL
		|| unit_map[cell_top][cell_right] == WALL
		|| unit_map[cell_bottom][cell_left] == WALL
		|| unit_map[cell_bottom][cell_right] == WALL)
	{
		return (0);
	}
	return (1);
}

int	open_closed_door(t_char *player, double x, double y)
{
	t_door	*door;

	door = find_door(player->data->door_list, x, y);
	if (door && door->state != OPEN)
		return (0);
	else
		return (1);
}

int	can_move_door(t_char *player, double new_x, double new_y)
{
	int		cell_top;
	int		cell_bottom;
	int		cell_left;
	int		cell_right;
	char	**unit_map;

	unit_map = player->data->unit_map;
	cell_top = floor((new_y - player->hitbox_radius));
	cell_bottom = floor((new_y + player->hitbox_radius));
	cell_left = floor((new_x - player->hitbox_radius));
	cell_right = floor((new_x + player->hitbox_radius));
	if (cell_top < 0 || cell_left < 0 || cell_bottom >= player->data->map_h
		* BLOCK_SIZE || cell_right >= player->data->map_w * BLOCK_SIZE)
	{
		return (0);
	}
	if (unit_map[cell_top][cell_left] == DOOR
		|| unit_map[cell_top][cell_right] == DOOR
		|| unit_map[cell_bottom][cell_left] == DOOR
		|| unit_map[cell_bottom][cell_right] == DOOR)
	{
		return (open_closed_door(player, new_x, new_y));
	}
	return (1);
}

int	check_for_wall_collision(t_char *player, double new_x, double new_y)
{
	if (!can_move_wall(player, new_x, new_y))
	{
		return (1);
	}
	if (!can_move_door(player, new_x, new_y))
	{
		return (1);
	}
	return (0);
}
