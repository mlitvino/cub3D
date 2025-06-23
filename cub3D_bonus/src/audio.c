/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:21:27 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/24 00:57:31 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static const char	*g_sound_path[MAX_SOUND] = {
[S_DOOR] = S_DOOR_PATH,
[S_SHOT] = S_SHOT_PATH,
[S_RELOADING] = S_RELOADING_PATH,
[S_WOLF_GROWL] = S_WOLF_GROWL_PATH,
[S_STATUE_HUM] = S_STATUE_HUM_PATH
};

static const char	*g_music_path[MAX_MUSIC] = {
[M_STORM] = M_STORM_PATH,
[M_FOREST] = M_FOREST_PATH,
[M_WOLF_STEP] = M_WOLF_STEP_PATH,
[M_PLAYER_STEP] = M_PLAYER_STEP_PATH
};

void	clean_audio(t_data *data)
{
	int	i;

	i = 0;
	while (i < MAX_SOUND)
		UnloadSound(data->sound[i++]);
	i = 0;
	while (i < MAX_MUSIC)
		UnloadMusicStream(data->music[i++]);
	CloseAudioDevice();
}

void	init_audio(t_data *data)
{
	int	i;

	ft_bzero(&data->sound[0], sizeof(Sound) * MAX_SOUND);
	ft_bzero(&data->music[0], sizeof(Music) * MAX_MUSIC);
	SetTraceLogLevel(LOG_ERROR);
	InitAudioDevice();
	if (IsAudioDeviceReady() == false)
		clean_all(data, NULL);
	i = 0;
	while (i < MAX_SOUND)
	{
		data->sound[i] = LoadSound(g_sound_path[i]);
		if (IsSoundValid(data->sound[i]) == false)
			clean_all(data, NULL);
		i++;
	}
	i = 0;
	while (i < MAX_MUSIC)
	{
		data->music[i] = LoadMusicStream(g_music_path[i]);
		if (IsMusicValid(data->music[i]) == false)
			clean_all(data, NULL);
		i++;
	}
}
