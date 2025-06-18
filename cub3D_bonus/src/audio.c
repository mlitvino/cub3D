#include "cub3D.h"

void	init_audio(t_data *data)
{
	InitAudioDevice();

	data->test3 = LoadSound("./audio/coin.wav");
	Music test1;
}

