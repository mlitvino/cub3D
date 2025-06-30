/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:02:35 by ablodorn          #+#    #+#             */
/*   Updated: 2025/06/30 16:02:53 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	resize_handler(int32_t width, int32_t height, void *data_arg)
{
	t_data	*data;

	data = (t_data *)data_arg;
	data->mlx_data.scr_size.x = width;
	data->mlx_data.scr_size.y = height;
}

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_data	*data;
	t_keys	*keys;

	(void)mods;
	data = (t_data *)param;
	keys = &data->keys;
	if (button == MLX_MOUSE_BUTTON_LEFT)
	{
		if (action == MLX_PRESS)
		{
			keys->click = true;
			mlx_get_mouse_pos(data->mlx_data.mlx_ptr, &keys->click_pos.x,
				&keys->click_pos.y);
		}
		else if (action == MLX_RELEASE)
			keys->click = false;
	}
}

static void	set_key_flag(t_keys *k, mlx_key_data_t keydata, int value,
		t_data *data)
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
	else if (keydata.key == MLX_KEY_UP)
		k->up = value;
	else if (keydata.key == MLX_KEY_DOWN)
		k->down = value;
	else if (keydata.key == MLX_KEY_ESCAPE)
		k->esc = value;
	else if (keydata.key == MLX_KEY_TAB)
		k->tab = value;
	else if (keydata.key == MLX_KEY_E)
		k->e = value;
	data->player.is_moving = (k->w || k->a || k->s || k->d);
}

void	change_sprite_state(t_data *data, int type, int new_state)
{
	t_sprite	*sprite;

	sprite = data->sprite_list;
	while (sprite)
	{
		if (sprite->type == type)
		{
			sprite->state = new_state;
			sprite->cur_img = sprite->tex_imgs[new_state];
		}
		sprite = sprite->next;
	}
}

void	key_event_handler(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_SPACE)
		open_close_door(data);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_all(data, NULL);
	if (keydata.action == MLX_PRESS)
		set_key_flag(&data->keys, keydata, 1, data);
	else if (keydata.action == MLX_RELEASE)
		set_key_flag(&data->keys, keydata, 0, data);
	if (keydata.action == MLX_RELEASE && keydata.key == MLX_KEY_T)
	{
		data->keys.cursor = !data->keys.cursor;
		if (data->keys.cursor)
			mlx_set_cursor_mode(data->mlx_data.mlx_ptr, MLX_MOUSE_NORMAL);
		else
			mlx_set_cursor_mode(data->mlx_data.mlx_ptr, MLX_MOUSE_HIDDEN);
	}
}
