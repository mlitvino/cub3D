/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:23:13 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/30 14:25:30 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_sprite_tex(t_sprite *new_sprite, t_data *data, int type)
{
	new_sprite->tex_imgs = data->mlx_data.textrs_img;
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
	else if (type == EXIT)
		new_sprite->cur_img = new_sprite->tex_imgs[EXIT_TEX];
	else if (type == DEAD_MAN)
		new_sprite->cur_img = new_sprite->tex_imgs[DEAD_MAN_TEX];
	else if (type == AMMO)
		new_sprite->cur_img = new_sprite->tex_imgs[AMMO_TEX];
	else if (type == TREE)
		new_sprite->cur_img = new_sprite->tex_imgs[EVIL_TREE];
	else if (type == WOODPILE)
		new_sprite->cur_img = new_sprite->tex_imgs[WOODPILE_TEX];
	else if (type == BONES)
		new_sprite->cur_img = new_sprite->tex_imgs[BONES_TEX];
}

void	fill_sprite_info(t_sprite *new_sprite, t_data *data, int type)
{
	if (type == AMMO || type == DEAD_MAN || type == EXIT)
		new_sprite->walkable = true;
	else
		new_sprite->walkable = false;
	new_sprite->hp = ENEMY_HP;
	new_sprite->visible = true;
	new_sprite->type = type;
	new_sprite->hitbox_radius = BLOCK_SIZE / 2;
	new_sprite->move_spd = BLOCK_SIZE / 24;
	new_sprite->turn_spd = 2;
	new_sprite->dist = 0;
	new_sprite->path = NULL;
	new_sprite->moved = 0;
	new_sprite->has_player_in_sight = 0;
	new_sprite->move_rate = 0;
	new_sprite->attack_rate = 0;
	new_sprite->attack_range = 4.0f * data->player.hitbox_radius;
}

t_sprite	*create_sprite(t_data *data, int type, int grid_x, int grid_y)
{
	t_sprite	*new_sprite;
	t_sprite	*temp;

	new_sprite = malloc(sizeof(t_sprite));
	if (!new_sprite)
		return (NULL);
	set_sprite_tex(new_sprite, data, type);
	fill_sprite_info(new_sprite, data, type);
	new_sprite->pos.y = (grid_y * BLOCK_SIZE) + BLOCK_SIZE / 2;
	new_sprite->pos.x = (grid_x * BLOCK_SIZE) + BLOCK_SIZE / 2;
	new_sprite->next = NULL;
	new_sprite->move_rate = 0;
	new_sprite->attack_range = 4.0f * data->player.hitbox_radius;
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
	sprite_count = 0;
	temp = raycast->data->sprite_list;
	while (temp)
	{
		if (temp->visible == true)
			sprite_array[sprite_count++] = temp;
		temp = temp->next;
	}
	raycast->sprite_count = sprite_count;
	return (sprite_array);
}
