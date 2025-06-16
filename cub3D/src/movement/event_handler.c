#include "cub3D.h"

static void	set_key_flag(t_keys *k, mlx_key_data_t keydata, int value)
{
	if (keydata.key == MLX_KEY_W)
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

void	key_event_handler(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == 'R')
	{
		data->plane.center.y += 200;
	}
	if (keydata.key == 'T')
	{
		data->plane.center.y -= 200;
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(data->mlx_data.mlx_ptr);
		return ;
	}
	if (keydata.action == MLX_PRESS)
		set_key_flag(&data->keys, keydata, 1);
	else if (keydata.action == MLX_RELEASE)
		set_key_flag(&data->keys, keydata, 0);
}
