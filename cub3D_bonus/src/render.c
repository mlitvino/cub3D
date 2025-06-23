#include "cub3D.h"

static void update_bobbing(t_char *player, double delta_time)
{
	if (player->is_moving)
	{
		player->bobbing_time += delta_time * 10.0; // Tune the speed of bobbing
		player->height = 2 + (-sin(player->bobbing_time)) * 0.2;
	}
	else
	{
		if (fabs(player->height - player->height) > 0.1)
			player->height = player->height * 0.9 + player->height * 0.1;
		else
		{
			player->height = 2;
			player->bobbing_time = 0;
		}
	}
}

long get_time_in_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void	update_statue(t_data *data, t_char *player, t_sprite *sprites)
{
	static int	alpha;
	int			step;

	step = 1;
	while (sprites)
	{
		if (sprites->type == STATUE)
		{
			if (sprites->dist < STATUE_MAX_VIS * BLOCK_SIZE)
			{
				sprites->state = STATUE_RED;
				sprites->cur_img = data->mlx_data.textrs_img[STATUE_RED];
			}
			else
			{
				sprites->state = STATUE_GREY;
				sprites->cur_img = data->mlx_data.textrs_img[STATUE_GREY];
			}
		}
		sprites = sprites->next;
	}

	if (player->facing_statue)
	{
		if (alpha >= 255)
			data->game_state = DEATH;
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
	}
	else
		data->mlx_data.textrs_img[STATUE_FACE]->enabled = 0;
}

int	check_mouse_click(t_data *data, t_point *but)
{
	t_point	*m_clck;

	m_clck = &data->mouse_click;
	if (!(but->x < m_clck->x && m_clck->x < but->x + BUTTON_DX))
		return (-1);
	if (but->y < m_clck->y && m_clck->y < but->y + BUTTON_DY)
	{
		return (START);
	}
	else if (but->y + BUTTON_DY + BUTTON_DY2 < m_clck->y
		&& m_clck->y < but->y + (BUTTON_DY * 2) + BUTTON_DY2)
	{
		return (CONTROLS);
	}
	else if (but->y + (BUTTON_DY + BUTTON_DY2) * 2 < m_clck->y
		&& m_clck->y < but->y + (BUTTON_DY + BUTTON_DY2) * 2 + BUTTON_DY)
	{
		return (EXIT);
	}
	return (-1);
}

void	manage_menu(t_data *data, mlx_image_t **tex_img)
{
	mlx_image_t	*cur_menu;
	int			res;

	cur_menu = tex_img[data->game_state];
	cur_menu->enabled = 1;
	res = -1;
	// if (!mouse_click)
	// 	return ;
	if (data->game_state == MAIN_MENU /* || data->game_state == DEATH || data->game_state == CONTROLS*/)
		res = check_mouse_click(data, &data->main_button);
	else if (data->game_state == PAUSE /* || data->game_state == WIN*/)
		res = check_mouse_click(data, &data->pause_button);
	if (res != -1)
	{
		cur_menu->enabled = 0;
		if (res == EXIT)
			clean_all(data, NULL);
		else if (res == START)
			data->game_state = START;
		else if (res == CONTROLS)
			tex_img[CONTROLS]->enabled = 1;
	}
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
	// if (data->game_state == START)
	// 	if (IsMusicStreamPlaying(data->music[M_FOREST]) == false)
	// 		PlayMusicStream(data->music[M_FOREST]);
}

void	render(void *data_arg)
{
	t_data	*data;
	static long previous_time = 0;
	long current_time;
	double delta_time;

	data = (t_data *)data_arg;

	// handle mouse_click
	current_time = get_time_in_ms();
	delta_time = (current_time - previous_time) / 1000.0;
	previous_time = current_time;
	if (data->game_state == START)
	{
		if (data->keys.w)
			move_player(&data->player, 0);
		if (data->keys.a)
			move_player(&data->player, 90);
		if (data->keys.s)
			move_player(&data->player, 180);
		if (data->keys.d)
			move_player(&data->player, -90);

		if (data->keys.w || data->keys.a || data->keys.s || data->keys.d)
			ResumeMusicStream(data->music[M_PLAYER_STEP]);
		else
			PauseMusicStream(data->music[M_PLAYER_STEP]);

		if (data->keys.left)
			rotate_player_right(&data->player);
		if (data->keys.right)
			rotate_player_left(&data->player);

		if (data->keys.tab)
			data->game_state = PAUSE;

		// update_bobbing(&data->player, delta_time);
		// handle_mouse_rotation(data);
		update_doors(data->door_list, data);
		update_statue(data, &data->player, data->sprite_list);
		raycast(data);
		show_fps();
		draw_minimap(data, data->mlx_data.minimap);
		draw_aim_cross(data->mlx_data.scr_img);
	}
	else
	{
		manage_menu(data, data->mlx_data.textrs_img);
	}
	update_audio(data);
}
