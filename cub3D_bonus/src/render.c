#include "cub3D.h"

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
	// 	{ }
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

void	render(void *data_arg)
{
	t_data	*data;

	data = (t_data *)data_arg;

	// handle mouse_click
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

		// handle_mouse_rotation(data);
		update_doors(data->door_list);
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

	for (int i = 0; i < MAX_MUSIC; i++)
	{
		UpdateMusicStream(data->music[i]);
	}
}
