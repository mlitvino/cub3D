/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:43:06 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/02 16:50:18 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	compre_dist(t_raycast *raycast, t_wall *hor_wall, t_wall *ver_wall)
{
	if (hor_wall->dist < ver_wall->dist)
	{
		raycast->rays_dist[raycast->cur_ray] = hor_wall->dist;
		raycast->axis = HORIZONT;
		select_tex(raycast, hor_wall, HORIZONT);
		render_col(raycast, hor_wall, hor_wall->dist, raycast->tex_indx);
	}
	else if (ver_wall->dist < hor_wall->dist)
	{
		raycast->rays_dist[raycast->cur_ray] = ver_wall->dist;
		raycast->axis = VERTICAL;
		select_tex(raycast, ver_wall, VERTICAL);
		render_col(raycast, ver_wall, ver_wall->dist, raycast->tex_indx);
	}
	else if (hor_wall->dist != INT_MAX
		&& raycast->unit_map[hor_wall->pos.y][hor_wall->pos.x - 1] == WALL
		&& raycast->unit_map[hor_wall->pos.y][hor_wall->pos.x + 1] == WALL)
	{
		raycast->rays_dist[raycast->cur_ray] = hor_wall->dist;
		raycast->axis = HORIZONT;
		select_tex(raycast, hor_wall, HORIZONT);
		render_col(raycast, hor_wall, hor_wall->dist, raycast->tex_indx);
	}
	else
	{
		raycast->rays_dist[raycast->cur_ray] = ver_wall->dist;
		raycast->axis = VERTICAL;
		select_tex(raycast, ver_wall, VERTICAL);
		render_col(raycast, ver_wall, ver_wall->dist, raycast->tex_indx);
	}
}

void	cast_ray(t_raycast *raycast, double ray_angl)
{
	if ((int)ray_angl != 180 && (int)ray_angl != 0)
		find_wall(raycast, &raycast->hor_wall, HORIZONT);
	else
		raycast->hor_wall.dist = INT_MAX;
	if ((int)ray_angl != 90 && (int)ray_angl != 270)
		find_wall(raycast, &raycast->ver_wall, VERTICAL);
	else
		raycast->ver_wall.dist = INT_MAX;
	calc_norm_dist(raycast);
	compre_dist(raycast, &raycast->hor_wall, &raycast->ver_wall);
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
		clean_all(raycast->data);
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

void	calc_sprite_dist(t_raycast *raycast, t_sprite **sprite_array)
{
	int	i;
	int	temp_dist;

	i = 0;
	while (i < raycast->sprite_count)
	{
		temp_dist = calc_dist(raycast->char_pos, sprite_array[i]->pos);
		sprite_array[i]->dist = temp_dist;
		i++;
	}
}

void	sort_sprite_dist(t_raycast *raycast, t_sprite **sprite_array)
{
	int			i;
	int			j;
	t_sprite	*temp;

	i = 0;
	while (i < raycast->sprite_count - 1)
	{
		j = i + 1;
		while (j < raycast->sprite_count)
		{
			if (sprite_array[i]->dist < sprite_array[j]->dist)
			{
				temp = sprite_array[i];
				sprite_array[i] = sprite_array[j];
				sprite_array[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	handle_sprites(t_raycast *raycast)
{
	t_sprite	**sprite_array;

	sprite_array = init_spite_array(raycast);
	calc_sprite_dist(raycast, sprite_array);
	//show_sprites(sprite_array, NULL);
	sort_sprite_dist(raycast, sprite_array);
	//show_sprites(sprite_array, NULL); 

	free(sprite_array);
}

void	raycast(t_data *data)
{
	t_raycast	raycast;
	int			cur_ray;
	double		cur_angle;

	raycast = init_raycast(data, &data->player);
	cur_ray = 0;
	cur_angle = raycast.ray_angle;
	while (cur_ray < data->rays_count)
	{
		fill_ray_info(&raycast);
		cast_ray(&raycast, raycast.ray_angle);
		cur_ray++;
		cur_angle -= data->rays_angle;
		if (cur_angle < 0)
			cur_angle = 360 + cur_angle;
		raycast.ray_angle = cur_angle;
		raycast.cur_ray = cur_ray;
	}
	if (data->sprite_list)
		handle_sprites(&raycast);
}
