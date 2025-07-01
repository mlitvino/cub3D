/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:59:13 by ablodorn          #+#    #+#             */
/*   Updated: 2025/07/01 14:59:14 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
