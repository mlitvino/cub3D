#include "cub3D.h"

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

void	init_audio_path(t_data *data)
{
	data->sound_path[S_DOOR] = S_DOOR_PATH;
	data->sound_path[S_SHOT] = S_SHOT_PATH;
	data->sound_path[S_RELOADING] = S_RELOADING_PATH;
	data->music_path[M_STORM] = M_STORM_PATH;
	data->music_path[M_FOREST] = M_FOREST_PATH;
	data->music_path[M_WOLF_STEP] = M_WOLF_STEP_PATH;
	data->music_path[M_PLAYER_STEP] = M_PLAYER_STEP_PATH;
}

void	init_audio(t_data *data)
{
	int	i;

	ft_bzero(&data->sound[0], sizeof(Sound) * MAX_SOUND);
	ft_bzero(&data->music[0], sizeof(Music) * MAX_MUSIC);
	SetTraceLogLevel(LOG_INFO);
	InitAudioDevice();
	if (IsAudioDeviceReady() == false)
		clean_all(data);
	i = 0;
	init_audio_path(data);
	while (i < MAX_SOUND)
	{
		data->sound[i] = LoadSound(data->sound_path[i]);
		if (IsSoundValid(data->sound[i]) == false)
			clean_all(data);
		i++;
	}
	i = 0;
	while (i < MAX_MUSIC)
	{
		data->music[i] = LoadMusicStream(data->music_path[i]);
		if (IsMusicValid(data->music[i]) == false)
			clean_all(data);
		i++;
	}
}
