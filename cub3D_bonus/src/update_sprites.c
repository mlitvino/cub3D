#include "cub3D.h"

void	update_statue_alpha(t_data *data, t_char *player)
{
	static double	alpha;
	double			step;

	step = data->fps / 80.0;
	if (player->facing_statue)
	{
		if (alpha + step > 255)
			change_game_state(data, DEATH);
		alpha += step;
	}
	else if (alpha > 0)
		alpha -= step;
	if (alpha > 0)
	{
		data->mlx_data.textrs_img[STATUE_FACE]->enabled = 1;
		adjust_image_alpha(data->mlx_data.textrs_img[STATUE_FACE], alpha);
		SetSoundVolume(data->sound[S_STATUE_HUM], (double)alpha / 155);
	}
	else
		data->mlx_data.textrs_img[STATUE_FACE]->enabled = 0;
}

void	update_statue(t_data *data, t_char *player, t_sprite *statue)
{
	if (statue->dist < STATUE_MAX_VIS * BLOCK_SIZE)
	{
		statue->state = STATUE_RED;
		statue->cur_img = data->mlx_data.textrs_img[STATUE_RED];
	}
	else
	{
		statue->state = STATUE_GREY;
		statue->cur_img = data->mlx_data.textrs_img[STATUE_GREY];
	}
	update_statue_alpha(data, player);
}

void	update_sprites(t_data *data, t_sprite *sprites)
{
	while (sprites)
	{
		if (sprites->type == WOLF && sprites->state != WOLF_DEAD)
		{
			update_wolf(data);
		}
		else if (sprites->type == STATUE)
			update_statue(data, &data->player, sprites);
		else if (sprites->type == EXIT)
		{
			if (sprites->dist < BLOCK_SIZE / 2)
				change_game_state(data, WIN);
		}
		else if (sprites->type == AMMO)
		{
			if (sprites->dist < BLOCK_SIZE / 2 && sprites->visible == true
				&& data->player.ammo < 9)
			{
				data->player.ammo++;
				sprites->visible = false;
			}
		}
		sprites = sprites->next;
	}
}
