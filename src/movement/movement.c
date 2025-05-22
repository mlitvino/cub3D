#include "cub3D.h"

void move_player(t_char *player, double angle_offset)
{
    double angle_rad;
    double dx;
    double dy;
    double new_x;
    double new_y;

    angle_rad = DEG_TO_RAD(player->pov.view_angl + angle_offset);
    dx = cos(angle_rad) * player->move_spd;
    dy = sin(angle_rad) * player->move_spd;
    new_x = player->pos.x + dx;
    new_y = player->pos.y + dy;
    if (!check_for_wall_collision(player, new_x, new_y))
    {
        player->pos.x += dx;
        player->pos.y += dy;
    }
}

int check_for_wall_collision(t_char *player, double new_x, double new_y)
{
    int     cell_top;
    int     cell_bottom;
    int     cell_left;
    int     cell_right;
    char    **unit_map;
    int     rows;
    int     cols;

    rows = player->data->map_h;
    cols = player->data->map_w;
    unit_map = player->data->unit_map;
    cell_top    = floor((new_y - player.hitbox_radius) / BLOCK_SIZE);
    cell_bottom = floor((new_y + player.hitbox_radius) / BLOCK_SIZE);
    cell_left   = floor((new_x - player.hitbox_radius) / BLOCK_SIZE);
    cell_right  = floor((new_x + player.hitbox_radius) / BLOCK_SIZE);
    if (cell_top < 0 || cell_left < 0 ||
        cell_bottom >= rows || cell_right >= cols)
        return 1;
    if (unit_map[cell_top][cell_left] == '1' ||
    unit_map[cell_top][cell_right] == '1' ||
    unit_map[cell_bottom][cell_left] == '1' ||
    unit_map[cell_bottom][cell_right] == '1')
        return (1);
    return (0);
}

