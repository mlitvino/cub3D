#include "cub3D.h"

long get_time_in_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

static void update_bobbing(t_char *player)
{
	static long	previous_time;
	long		current_time;
	double		delta_time;

	current_time = get_time_in_ms();
	delta_time = (current_time - previous_time) / 1000.0;
	previous_time = current_time;
	if (player->is_moving)
	{
		player->bobbing_time += delta_time * 10.0; // Tune the speed of bobbing
		player->height = BLOCK_SIZE /2 + sin(player->bobbing_time) * 50;
	}
	else
	{
		if (fabs(player->height - player->height) > 0.1)
			player->height = player->height * 0.9 + player->height * 0.1;
		else
		{
			player->height = BLOCK_SIZE / 2 ;
			player->bobbing_time = 0;
		}
	}
	player->wall_rt = 1 + (player->height / (BLOCK_SIZE / 2));
	player->ceiling_rt = BLOCK_SIZE / (1 + ((BLOCK_SIZE / 2)
				/ (BLOCK_SIZE - player->height)));
	player->floor_rt = BLOCK_SIZE / (1 + ((BLOCK_SIZE / 2)
				/ player->height));
}

void	update_statue(t_data *data, t_char *player, t_sprite *statue)
{
	static int	alpha;
	int			step;

	step = 1;
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
	if (player->facing_statue)
	{
		if (alpha >= 255)
		{
			StopSound(data->sound[S_STATUE_HUM]);
			die(data, NULL);
		}
		alpha += step;
		if (alpha > 255)
			alpha = 255;
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

void	update_audio(t_data *data)
{
	int	i;

	i = 0;
	while (i < MAX_MUSIC)
		UpdateMusicStream(data->music[i++]);
	if (data->game_state == MAIN_MENU)
		if (IsMusicStreamPlaying(data->music[M_STORM]) == false)
			PlayMusicStream(data->music[M_STORM]);
	if (data->game_state == START)
	{
		if (IsMusicStreamPlaying(data->music[M_FOREST]) == false)
			PlayMusicStream(data->music[M_FOREST]);
		if (IsSoundPlaying(data->sound[S_STATUE_HUM]) == false)
			PlaySound(data->sound[S_STATUE_HUM]);
	}
}

void	update_sprites(t_data *data, t_sprite *sprites)
{
	while (sprites)
	{
		if (sprites->type == WOLF)
		{
			//update_wolf();
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
			if (sprites->dist < BLOCK_SIZE / 2 && sprites->visible == true)
			{
				data->player.ammo++;
				sprites->visible = false;
			}
		}
		else
		{
			//update_other();
		}
		sprites = sprites->next;
	}
}

void	update_player(t_data *data, t_keys *keys, t_char *player)
{
	if (player->hp == 0)
		die(data, NULL);
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

	if (keys->click || keys->e)
		shoot(data, player);

	if (player->is_shooting == true && player->ammo > 0
		&& IsSoundPlaying(data->sound[S_SHOT]) == false)
	{
		player->is_shooting = false;
		data->mlx_data.textrs_img[CROSSBOW1]->enabled = true;
		data->mlx_data.textrs_img[CROSSBOW2]->enabled = false;
	}
	handle_mouse_rotation(data);
	update_bobbing(player);
}

void	render(void *data_arg)
{
	t_data	*data;

	data = (t_data *)data_arg;
	if (data->game_state == START)
	{
		show_fps();
		raycast(data);
		draw_minimap(data, data->mlx_data.minimap);
		draw_aim_cross(data->mlx_data.scr_img);
		update_player(data, &data->keys, &data->player);
		update_doors(data->door_list, data);
		update_sprites(data, data->sprite_list);
	}
	else
	{
		manage_menu(data, data->mlx_data.textrs_img);
	}
	update_audio(data);
}
