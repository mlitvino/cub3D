#include "cub3D.h"

void	rotate_player_right(t_char *player)
{
	player->pov.view_angl += player->turn_spd;
	if (player->pov.view_angl >= 360)
		player->pov.view_angl -= 360;
}

void	rotate_player_left(t_char *player)
{
	player->pov.view_angl -= player->turn_spd;
	if (player->pov.view_angl < 0)
		player->pov.view_angl += 360;
}

void handle_mouse_rotation(t_data *game)
{
	int x;
	int y;
	int center_x = WIN_W / 2;
	int center_y = WIN_H / 2;
	int delta_x;
	int delta_y;
	float sensitivity = 0.06f;
	int vertical_speed = 1;

	mlx_get_mouse_pos(game->mlx_data.mlx_ptr, &x, &y);
	delta_x = x - center_x;
	delta_y = y - center_y;
	game->player.pov.view_angl -= delta_x * sensitivity;

	if (game->player.pov.view_angl >= 360)
		game->player.pov.view_angl -= 360;
	else if (game->player.pov.view_angl < 0)
		game->player.pov.view_angl += 360;

	game->plane.center.y -= (delta_y * vertical_speed) / 2;

	if (game->plane.center.y > WIN_H+400)
		game->plane.center.y = WIN_H+400;
	else if (game->plane.center.y < -400)
		game->plane.center.y = -400;

	mlx_set_mouse_pos(game->mlx_data.mlx_ptr, center_x, center_y);
}
