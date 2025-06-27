#include "cub3D.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void	update_player_ratio(t_char *player)
{
	player->wall_rt = 1 + (player->height / (BLOCK_SIZE / 2));
	player->ceiling_rt = BLOCK_SIZE / (1 + ((BLOCK_SIZE / 2) / (BLOCK_SIZE
					- player->height)));
	player->floor_rt = BLOCK_SIZE / (1 + ((BLOCK_SIZE / 2) / player->height));
}

void	update_bobbing(t_char *player)
{
	static long	previous_time;
	long		current_time;
	double		delta_time;

	current_time = get_time_in_ms();
	delta_time = (current_time - previous_time) / 1000.0;
	previous_time = current_time;
	if (player->is_moving)
	{
		player->bobbing_time += delta_time * 10.0;
		player->height = BLOCK_SIZE / 2 + sin(player->bobbing_time) * 50;
	}
	else
	{
		if (fabs(player->height - player->height) > 0.1)
			player->height = player->height * 0.9 + player->height * 0.1;
		else
		{
			player->height = BLOCK_SIZE / 2;
			player->bobbing_time = 0;
		}
	}
	update_player_ratio(player);
}

void	check_keys(t_data *data, t_keys *keys, t_char *player)
{
	if (keys->w)
		move_player(player, 0);
	if (keys->a)
		move_player(player, 90);
	if (keys->s)
		move_player(player, 180);
	if (keys->d)
		move_player(player, -90);
	if (keys->w || keys->a || keys->s || keys->d)
		ResumeMusicStream(data->music[M_PLAYER_STEP]);
	else
		PauseMusicStream(data->music[M_PLAYER_STEP]);
	if (keys->left)
		rotate_player_right(player);
	if (keys->right)
		rotate_player_left(player);
	if (keys->up)
		data->plane.center.y += 33;
	if (keys->down)
		data->plane.center.y -= 34;
	if (keys->tab)
		change_game_state(data, PAUSE);
	if (data->keys.click ||data->keys.e)
		shoot(data, player);
}

void	update_player(t_data *data, t_char *player)
{
	check_keys(data, &data->keys, &data->player);
	if (!data->keys.cursor)
		handle_mouse_rotation(data);
	update_bobbing(player);
	if (player->is_shooting == true && player->ammo > 0
	&& IsSoundPlaying(data->sound[S_SHOT]) == false)
	{
		player->is_shooting = false;
		data->mlx_data.textrs_img[CROSSBOW1]->enabled = true;
		data->mlx_data.textrs_img[CROSSBOW2]->enabled = false;
	}
}
