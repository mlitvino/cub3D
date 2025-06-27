/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:21:27 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/28 01:23:55 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static const char	*g_sound_path[MAX_SOUND] = {
[S_VICTORY] = S_VICTORY_PATH,
[S_MET_DOOR] = S_MET_DOOR_PATH,
[S_STONE_DOOR] = S_STONE_DOOR_PATH,
[S_DOOR] = S_DOOR_PATH,
[S_SHOT] = S_SHOT_PATH,
[S_WOLF_CHASE] = S_WOLF_CHASE_PATH,
[S_WOLF_GROWL] = S_WOLF_GROWL_PATH,
[S_STATUE_HUM] = S_STATUE_HUM_PATH,
[S_PLAYER_DYING] = S_PLAYER_DYING_PATH
};

static const char	*g_music_path[MAX_MUSIC] = {
[M_CASTLE] = M_CASTLE_PATH,
[M_STORM] = M_STORM_PATH,
[M_FOREST] = M_FOREST_PATH,
[M_WOLF_STEP] = M_WOLF_STEP_PATH,
[M_PLAYER_STEP] = M_PLAYER_STEP_PATH
};

void	tune_audio(t_data *data, char *map_name)
{
	PlaySound(data->sound[S_STATUE_HUM]);
	SetMusicVolume(data->music[M_FOREST], 0.5);
	SetMusicVolume(data->music[M_CASTLE], 0.3);
	SetSoundVolume(data->sound[S_STATUE_HUM], 0);
	SetSoundVolume(data->sound[S_MET_DOOR], 0.5);
	SetSoundVolume(data->sound[S_SHOT], 2);
	//PlayMusicStream(data->music[M_STORM]);
	if (ft_strncmp(map_name, "map/forest", 6) == 0)
		data->main_music = &data->music[M_FOREST];
	else
		data->main_music = &data->music[M_CASTLE];
}

void	clean_audio(t_data *data)
{
	int	i;

	i = 0;
	while (i < MAX_SOUND)
	{
		if (IsSoundValid(data->sound[i]))
			UnloadSound(data->sound[i]);
		i++;
	}
	i = 0;
	while (i < MAX_MUSIC)
	{
		if (IsMusicValid(data->music[i]))
			UnloadMusicStream(data->music[i]);
		i++;
	}
	if (IsAudioDeviceReady())
		CloseAudioDevice();
}

void	init_audio(t_data *data)
{
	int	i;

	ft_bzero(&data->sound[0], sizeof(Sound) * MAX_SOUND);
	ft_bzero(&data->music[0], sizeof(Music) * MAX_MUSIC);
	SetTraceLogLevel(LOG_WARNING);
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
