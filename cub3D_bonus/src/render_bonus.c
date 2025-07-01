/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:51:51 by mlitvino          #+#    #+#             */
/*   Updated: 2025/07/01 17:42:27 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_aim_cross(mlx_image_t *scr_img)
{
	int	x;
	int	y;

	x = scr_img->width / 2 - 10;
	y = scr_img->height / 2;
	while (x < (int)scr_img->width / 2 + 10)
	{
		mlx_put_pixel(scr_img, x, y, 0xFF0000FF);
		x++;
	}
	y = scr_img->height / 2 - 10;
	x = scr_img->width / 2;
	while (y < (int)scr_img->height / 2 + 10)
	{
		mlx_put_pixel(scr_img, x, y, 0xFF0000FF);
		y++;
	}
}

void	show_fps(t_data *data)
{
	static struct timeval	last = {0, 0};
	static int				frames = 0;
	struct timeval			now;
	double					elapsed;

	gettimeofday(&now, NULL);
	if (last.tv_sec == 0 && last.tv_usec == 0)
	{
		last = now;
		return ;
	}
	frames++;
	elapsed = (now.tv_sec - last.tv_sec) + (now.tv_usec - last.tv_usec)
		/ 1000000.0;
	if (elapsed >= 1.0)
	{
		printf("FPS: %d\n", frames);
		data->fps = frames;
		frames = 0;
		last = now;
	}
}

void	update_audio(t_data *data)
{
	int	i;

	i = 0;
	while (i < MAX_MUSIC)
		UpdateMusicStream(data->music[i++]);
	if (data->game_state == START)
	{
		if (IsMusicStreamPlaying(*data->main_music) == false)
		{
			if (GetMusicTimePlayed(*data->main_music) > 0)
				ResumeMusicStream(*data->main_music);
			else
				PlayMusicStream(*data->main_music);
		}
		if (IsSoundPlaying(data->sound[S_STATUE_HUM]) == false)
			PlaySound(data->sound[S_STATUE_HUM]);
	}
}

void	update_hud(t_char *player, mlx_image_t **tex_img)
{
	static int	prev_hp;
	static int	prev_ammo;

	if (prev_hp != player->hp)
	{
		tex_img[N0_TEX + prev_hp]->instances[0].enabled = false;
		tex_img[N0_TEX + player->hp]->instances[0].enabled = true;
		prev_hp = player->hp;
	}
	if (prev_ammo != player->ammo)
	{
		tex_img[N0_TEX + prev_ammo]->instances[1].enabled = false;
		tex_img[N0_TEX + player->ammo]->instances[1].enabled = true;
		prev_ammo = player->ammo;
	}
}

void	render(void *data_arg)
{
	t_data	*data;

	data = (t_data *)data_arg;
	if (data->game_state == START)
	{
		show_fps(data);
		raycast(data);
		draw_minimap(data, data->mlx_data.minimap);
		draw_aim_cross(data->mlx_data.scr_img);
		update_player(data, &data->player);
		update_doors(data->door_list, data);
		update_sprites(data, data->sprite_list);
		update_hud(&data->player, data->mlx_data.textrs_img);
	}
	else
	{
		manage_menu(data, data->mlx_data.textrs_img, data->mlx_data.scr_size);
	}
	update_audio(data);
}
