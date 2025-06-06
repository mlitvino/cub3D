#include "cub3D.h"

/*void key_event_handler(mlx_key_data_t keydata, void *param)
{
	t_data *data;
	t_char *player;

	data = (t_data *)param;
	player = &data->player;

	// Only react on key press, not release
	if (keydata.action != MLX_PRESS)
		return;
	if (keydata.key == 'W')
		move_player(player, 0);
	else if (keydata.key == 'S')
		move_player(player, 180);
	else if (keydata.key == 'A')
		move_player(player, 90);
	else if (keydata.key == 'D')
		move_player(player, -90);
	else if (keydata.key == KEY_LEFT_ARROW)
		rotate_player_left(player);
	else if (keydata.key == KEY_RIGHT_ARROW)
		rotate_player_right(player);
	else if (keydata.key == 'C')
	{
		clean_all(data);
	}
	else if (keydata.key == 'E')
	{
		data->player.pov.view_angl += 5;
		if (data->player.pov.view_angl < 0)
			data->player.pov.view_angl = 360 + data->player.pov.view_angl;
	}
	else if (keydata.key == 'Q')
	{
		data->player.pov.view_angl -= 5;
		if (data->player.pov.view_angl < 0)
			data->player.pov.view_angl = 360 + data->player.pov.view_angl;
	}
	// raycast(data);
	// show_char_pos(data, player);
	// printf("view_angle: %d\n", player->pov.view_angl);
	// show_redline(data);
}*/

static void	set_key_flag(t_keys *k, mlx_key_data_t keydata, int value)
{
	if (keydata.key == 'W')
        k->w = value;
	else if (keydata.key == MLX_KEY_A)
        k->a = value;
	else if (keydata.key == MLX_KEY_S)
        k->s = value;
	else if (keydata.key == MLX_KEY_D)
        k->d = value;
	else if (keydata.key == MLX_KEY_LEFT)
        k->left = value;
	else if (keydata.key == MLX_KEY_RIGHT)
        k->right = value;
	else if (keydata.key == MLX_KEY_ESCAPE)
        k->esc = value;
}

void	change_wolf(t_data *data, int new_state)
{
	t_sprite *sprite;

	sprite = data->sprite_list;
	while (sprite)
	{
		sprite->state = new_state;
		sprite->cur_img = sprite->tex_imgs[new_state];

		sprite = sprite->next;
	}
}

void	key_event_handler(mlx_key_data_t keydata, void *param)
{
	t_data *data = (t_data *)param;

	if (keydata.key == 'R')
	{
		data->plane.center.y += 200;
	}
	else if (keydata.key == 'T')
	{
		data->plane.center.y -= 200;
	}


	if (keydata.key == '1')
	{
		change_wolf(data, WOLF_STAY);
	}
	if (keydata.key == '2')
	{
		change_wolf(data, WOLF_WALK1);
	}
	if (keydata.key == '3')
	{
		change_wolf(data, WOLF_WALK2);
	}
	if (keydata.key == '4')
	{
		change_wolf(data, WOLF_ATTCK);
	}


	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		clean_all(data);
		return ;
	}
	if (keydata.action == MLX_PRESS /*|| keydata.action == MLX_REPEAT*/)
		set_key_flag(&data->keys, keydata, 1);
	else if (keydata.action == MLX_RELEASE)
		set_key_flag(&data->keys, keydata, 0);
}
