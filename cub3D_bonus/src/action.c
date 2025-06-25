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
		change_game_state(data, DEATH);
	}
}

void	get_damage(t_data *data, t_sprite *spr, t_char *player)
{
	if (spr && spr->type == WOLF)
	{
		if (--spr->hp <= 0)
		{
			die(data, spr);
		}
	}
	else
	{
		if (--player->hp <= 0)
		{
			die(data, NULL);
		}
	}
}

void	shoot(t_data *data, t_char *player)
{
	t_sprite	*enemy;

	if (player->ammo > 0 && player->is_shooting == 0
		&& IsSoundPlaying(data->sound[S_SHOT]) == false)
	{
		enemy = player->facing_enemy;
		player->ammo--;
		player->is_shooting = true;
		if (enemy)
		{
			get_damage(data, enemy, player);
			printf("type_name: %s\n",
				enemy->type == WOLF ? "WOLF" : enemy->type == STATUE ? "STATUE" : "UNKNOWN");
			printf("x %d, y %d\n", enemy->pos.x, enemy->pos.y);
		}
		else
		{
			printf("Enemy is not in center of screen\n");
		}
		PlaySound(data->sound[S_SHOT]);
		data->mlx_data.textrs_img[CROSSBOW1]->enabled = false;
		data->mlx_data.textrs_img[CROSSBOW2]->enabled = true;
	}
}
