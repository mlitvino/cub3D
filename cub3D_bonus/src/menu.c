#include "cub3D.h"

void	change_game_state(t_data *data, int	new_state)
{
	int	i;

	i = 0;
	while (i < MAX_SOUND)
		StopSound(data->sound[i++]);
	i = 0;
	while (i < MAX_MUSIC)
		StopMusicStream(data->music[i++]);
	if (new_state == DEATH)
		PlaySound(data->sound[S_PLAYER_DYING]);
	else if (new_state == WIN)
		PlaySound(data->sound[S_VICTORY]);
	data->game_state = new_state;
}

int	check_mouse_click(t_data *data, t_point *but)
{
	t_point	*m_clck;

	m_clck = &data->keys.click_pos;
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
	if (!data->keys.click)
		return ;
	if (data->game_state == MAIN_MENU)
		res = check_mouse_click(data, &data->keys.main_button);
	else
		res = check_mouse_click(data, &data->keys.pause_button);
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
