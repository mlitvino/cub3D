/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:20:49 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/02 15:32:06 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_sprite	*create_sprite(t_data *data, int type, int grid_x, int grid_y)
{
	t_sprite	*new_sprite;
	t_sprite	*temp;

	new_sprite = malloc(sizeof(t_sprite));
	if (!new_sprite)
		return (NULL);
	if (type == WOLF)
	{
		new_sprite->tex_imgs = data->mlx_data.textrs_img;
		new_sprite->cur_img = new_sprite->tex_imgs[WOLF_STAY];
		new_sprite->tex_cur_img = WOLF_STAY;
		new_sprite->walkable = false;
		new_sprite->type = WOLF;

		// general?
		new_sprite->hitbox_radius = BLOCK_SIZE / 2;
		new_sprite->move_spd = BLOCK_SIZE / 16;
		new_sprite->turn_spd = 2;
		new_sprite->pos.y = (grid_y * BLOCK_SIZE) + BLOCK_SIZE / 2;
		new_sprite->pos.x = (grid_x * BLOCK_SIZE) + BLOCK_SIZE / 2;
		new_sprite->dist = 0;
	}
	new_sprite->next = NULL;
	temp = data->sprite_list;
	while (temp && temp->next)
		temp = temp->next;
	if (!temp)
		data->sprite_list = new_sprite;
	else if (!temp->next)
		temp->next = new_sprite;
	return (new_sprite);
}
