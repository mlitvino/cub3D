/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:23:13 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/27 16:08:01 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	fill_sprite_info(t_sprite *new_sprite, t_data *data, int type)
{
	new_sprite->tex_imgs = data->mlx_data.textrs_img;
	new_sprite->walkable = false;
	if (type == WOLF)
	{
		new_sprite->cur_img = new_sprite->tex_imgs[WOLF_STAY];
		new_sprite->state = WOLF_STAY;
	}
	else if (type == STATUE)
	{
		new_sprite->cur_img = new_sprite->tex_imgs[STATUE_GREY];
		new_sprite->state = STATUE_GREY;
	}
}

t_sprite	*create_sprite(t_data *data, int type, int grid_x, int grid_y)
{
	t_sprite	*new_sprite;
	t_sprite	*temp;

	new_sprite = malloc(sizeof(t_sprite));
	if (!new_sprite)
		return (NULL);
	fill_sprite_info(new_sprite, data, type);
	new_sprite->type = type;
	new_sprite->hitbox_radius = BLOCK_SIZE / 2;
	new_sprite->move_spd = BLOCK_SIZE / 24;
	new_sprite->turn_spd = 2;
	new_sprite->pos.y = (grid_y * BLOCK_SIZE) + BLOCK_SIZE / 2;
	new_sprite->pos.x = (grid_x * BLOCK_SIZE) + BLOCK_SIZE / 2;
	new_sprite->dist = 0;
	new_sprite->path = NULL;
	new_sprite->next = NULL;
	new_sprite->move_rate = 0;
	new_sprite->moved = 0;
	new_sprite->has_player_in_sight = 0;
	new_sprite->attack_range = BLOCK_SIZE;
	temp = data->sprite_list;
	
	while (temp && temp->next)
		temp = temp->next;
	if (!temp)
		data->sprite_list = new_sprite;
	else if (!temp->next)
		temp->next = new_sprite;
	return (new_sprite);
}

t_sprite	**init_spite_array(t_raycast *raycast)
{
	t_sprite	**sprite_array;
	t_sprite	*temp;
	int			sprite_count;

	sprite_count = 0;
	temp = raycast->data->sprite_list;
	while (temp)
	{
		sprite_count++;
		temp = temp->next;
	}
	sprite_array = ft_calloc(sprite_count + 1, sizeof(t_sprite *));
	if (!sprite_array)
		clean_all(raycast->data, "malloc");
	raycast->sprite_count = sprite_count;
	sprite_count = 0;
	temp = raycast->data->sprite_list;
	while (temp)
	{
		sprite_array[sprite_count++] = temp;
		temp = temp->next;
	}
	return (sprite_array);
}
