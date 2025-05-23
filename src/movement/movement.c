#include "cub3D.h"

void move_player(t_char *player, double angle_offset)
{
	double angle_rad;
	double dx;
	double dy;
	double new_x;
	double new_y;

	int tile_y = (int)(player->pos.y) / BLOCK_SIZE;
	int tile_x = (int)(player->pos.x) / BLOCK_SIZE;
	//printf("player is standing in tile  (%d, %d)\n", tile_y, tile_x);
	//printf("view_angle: %d\n", player->pov.view_angl);
	angle_rad = DEG_TO_RAD(player->pov.view_angl + angle_offset);
	//printf("angle_rad: %f\n", angle_rad);
	dx = cos(angle_rad) * (double)player->move_spd;
	dy = sin(angle_rad) * player->move_spd;
	//printf("old_postion x: %d\n", player->pos.x);
	//printf("old_postion y: %d\n", player->pos.y);
	new_x = player->pos.x + dx;
	new_y = player->pos.y + dy;
	//printf("old_postion x: %f\n", new_x);
	//printf("old_postion y: %f\n", new_y);
	if (!check_for_wall_collision(player, new_x, new_y))
	{
		player->pos.x += dx;
		player->pos.y += dy;
	}
	//player->pos.x += dx;
	//player->pos.y += dy;
}

int check_for_wall_collision(t_char *player, double new_x, double new_y)
{
	int     cell_top;
	int     cell_bottom;
	int     cell_left;
	int     cell_right;
	char    **unit_map;
	int     rows;
	int     cols;

	rows = player->data->map_h;
	//printf("rows: %d\n", rows);
	cols = player->data->map_w;
	//printf("cols: %d\n", cols);
	unit_map = player->data->unit_map;
	cell_top    = floor((new_y - player->hitbox_radius));
	cell_bottom = floor((new_y + player->hitbox_radius));
	cell_left   = floor((new_x - player->hitbox_radius));
	cell_right  = floor((new_x + player->hitbox_radius));
	if (cell_top < 0 || cell_left < 0 ||
		cell_bottom >= rows * BLOCK_SIZE || cell_right >= cols * BLOCK_SIZE)
	{
		return 1;
	}
	/*printf("cell_top: %d\n", cell_top);
	printf("cell_bottom: %d\n", cell_bottom);
	printf("cell_left: %d\n", cell_left);
	printf("cell_right: %d\n", cell_right);
	printf("cell: %d\n", unit_map[cell_top][cell_left]);*/
	if (unit_map[cell_top][cell_left] == WALL ||
	unit_map[cell_top][cell_right] == WALL ||
	unit_map[cell_bottom][cell_left] == WALL ||
	unit_map[cell_bottom][cell_right] == WALL)
	{
		return (1);
	}
	//is_can_go_throgh();
	return (0);
}
