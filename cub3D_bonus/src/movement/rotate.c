#include "cub3D.h"

void rotate_player_right(t_char *player)
{
    player->pov.view_angl += player->turn_spd;
    if (player->pov.view_angl >= 360)
        player->pov.view_angl -= 360;
}

void rotate_player_left(t_char *player)
{
    player->pov.view_angl -= player->turn_spd;
    if (player->pov.view_angl < 0)
        player->pov.view_angl += 360;
}

void handle_mouse_rotation(t_data *game)
{
	int	x;
	int	y;
	int	center_x;
	int	delta_x;
	float sensitivity = 0.09f; // Tune this for speed

	center_x = WIN_W / 2;
	// Get current mouse position
	mlx_get_mouse_pos(game->mlx_data.mlx_ptr, &x, &y);

	// Calculate how far mouse moved from center
	delta_x = x - center_x;

	if (delta_x > 0)
	{
		game->player.pov.view_angl -= delta_x * sensitivity;
		if (game->player.pov.view_angl >= 360)
			game->player.pov.view_angl -= 360;
	}
	else if (delta_x < 0)
	{
		game->player.pov.view_angl -= delta_x * sensitivity;
		if (game->player.pov.view_angl < 0)
			game->player.pov.view_angl += 360;
	}

	// Re-center the mouse after processing
	mlx_set_mouse_pos(game->mlx_data.mlx_ptr, center_x, WIN_H / 2);
}
