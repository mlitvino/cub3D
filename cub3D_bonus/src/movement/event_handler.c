#include "cub3D.h"


static void	set_key_flag(t_keys *k, mlx_key_data_t keydata, int value, t_data *data)
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
	data->player.is_moving = (k->w || k->a || k->s || k->d);
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
	if (keydata.key == MLX_KEY_SPACE /*&& is_center_door */)
	{
		open_close_door(data);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		clean_all(data);
		return ;
	}
	if (keydata.action == MLX_PRESS /*|| keydata.action == MLX_REPEAT*/)
		set_key_flag(&data->keys, keydata, 1, data);
	else if (keydata.action == MLX_RELEASE)
		set_key_flag(&data->keys, keydata, 0, data);
}
