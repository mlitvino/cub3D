#include "cub3D.h"

void	change_game_state(t_data *data, int	new_state)
{
	int	i;

	i = 0;
	while (i < MAX_SOUND)
		PauseSound(data->sound[i++]);
	i = 0;
	while (i < MAX_MUSIC)
		PauseMusicStream(data->music[i++]);
	if (new_state == DEATH)
		PlaySound(data->sound[S_PLAYER_DYING]);
	else if (new_state == WIN)
		PlaySound(data->sound[S_VICTORY]);
	data->game_state = new_state;
}

void	init_buttons(t_dpoint *but_r, t_point *d, int *dy2, t_point scr_size)
{
	but_r->x = scr_size.x / but_r->x;
	but_r->y = scr_size.y / but_r->y;
	d->x = scr_size.x / BUTTON_DX;
	d->y = scr_size.y / BUTTON_DY;
	*dy2 = scr_size.y / BUTTON_DY2;
}

int	check_mouse_click(t_data *data, t_dpoint but_r, t_point scr_size)
{
	t_point	*m_clck;
	t_point	d;
	int		dy2;

	m_clck = &data->keys.click_pos;
	init_buttons(&but_r, &d, &dy2, scr_size);
	if (!(but_r.x < m_clck->x && m_clck->x < but_r.x + d.x))
		return (-1);
	if (but_r.y < m_clck->y && m_clck->y < but_r.y + d.y)
	{
		return (START);
	}
	else if (but_r.y + d.y + dy2 < m_clck->y
		&& m_clck->y < but_r.y + (d.y * 2) + dy2)
	{
		return (CONTROLS);
	}
	else if (but_r.y + (d.y + dy2) * 2 < m_clck->y
		&& m_clck->y < but_r.y + (d.y + dy2) * 2 + d.y)
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
	if (!data->keys.click)
		return ;
	if (data->game_state == MAIN_MENU)
		res = check_mouse_click(data, MAIN_BUTTON, data->mlx_data.scr_size);
	else
		res = check_mouse_click(data, PAUSE_BUTTON, data->mlx_data.scr_size);
	if (res != -1)
	{
		data->keys.click = false;
		if (res != data->game_state)
			cur_menu->enabled = 0;
		if (res == EXIT)
			clean_all(data, NULL);
		else if (res == START)
			change_game_state(data, START);
		else if (res == CONTROLS)
			change_game_state(data, CONTROLS);
	}
}
