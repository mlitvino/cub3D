#include "cub3D.h"

void key_event_handler(mlx_key_data_t keydata, void *param)
{
    t_data *data;
    t_char *player;

	data = (t_data *)param;
	player = &data->player;

    // Only react on key press, not release
    if (keydata.action != MLX_PRESS)
        return;
    if (keydata.key == 'W')
        move_player(player, 180);
    else if (keydata.key == 'S')
        move_player(player, 0);
    else if (keydata.key == 'A')
        move_player(player, 90);
    else if (keydata.key == 'D')
        move_player(player, 270);
    else if (keydata.key == KEY_LEFT_ARROW)
        rotate_player_left(player);
    else if (keydata.key == KEY_RIGHT_ARROW)
        rotate_player_right(player);
    else if (keydata.key == KEY_ESC)
    {
        mlx_close_window(data->mlx_data.mlx_ptr);
    }
	show_unit_map(data);
	show_char_pos(data, &data->player);
}