#include "cub3D.h"

void	die(t_data *data, t_sprite *spr)
{
	if (spr)
	{
		spr->cur_img = spr->tex_imgs[WOLF_DEAD];
		spr->walkable = true;
		// PlaySound(data->sound[S_WOLF_DYING]);
	}
	else
	{
		data->game_state = DEATH; 
		PlaySound(data->sound[S_PLAYER_DYING]);
	}
}

void	get_damage(t_data *data)
{

}

void	finish_level(t_data *data)
{
	data->game_state = WIN;
}
