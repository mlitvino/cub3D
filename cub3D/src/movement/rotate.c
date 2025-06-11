#include "cub3D.h"

void rotate_player_right(t_char *player)
{
    player->pov.view_angl += player->turn_spd;
    if (player->pov.view_angl >= 360)
        player->pov.view_angl -= 360;
}

void rotate_player_left(t_char *player)
{
    player->pov.view_angl -= player->turn_spd;
    if (player->pov.view_angl < 0)
        player->pov.view_angl += 360;
}