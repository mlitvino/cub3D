/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:41:42 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/25 23:11:17 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static struct timeval	get_current_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now);
}

/*static int *check_for_door(char **map, int row, int col)
{
	int	delta_row;
	int	delta_col;
	int	n_row;
	int	n_col;
	int	*coordinates;

	row = row / BLOCK_SIZE;
	col = col / BLOCK_SIZE;
    delta_row = -1;
    while (delta_row <= 1)
    {
        delta_col = -1;
        while (delta_col <= 1)
        {
            if (!(delta_row == 0 && delta_col == 0))
            {
                n_row = row + delta_row;
                n_col = col + delta_col;
                if (map[n_row][n_col] == 'D')
                {
                    coordinates = malloc(2 * sizeof(int));
                    if (!coordinates)
                        return (NULL);
                    coordinates[0] = n_row;
                    coordinates[1] = n_col;
                    return (coordinates);
                }
            }
            delta_col++;
        }
        delta_row++;
    }
    return (NULL);
}*/

static int *check_for_door(char **map, int player_x, int player_y, t_data *data)
{
	int i;
	int *coordinates;
	double dir_x;
	double dir_y;
	double angle_rad;

	i = 0;
	angle_rad = DEG_TO_RAD(data->player.pov.view_angl);
	dir_x = cos(angle_rad);
	dir_y = -sin(angle_rad);

	//int front_x = (int)(data->player.pos.x + cos(angle_rad) * BLOCK_SIZE) / BLOCK_SIZE;
	//int front_y = (int)(data->player.pos.y + sin(angle_rad) * BLOCK_SIZE) / BLOCK_SIZE;

	//printf("Tile in front: (%d, %d) = %c\n", front_y, front_x, map[front_y][front_x]);
	while (i < 5)
	{
		player_x += dir_x * 80;
		player_y += dir_y * 80;

		if (ft_strchr(DOORS, map[(player_y /BLOCK_SIZE)][(player_x / BLOCK_SIZE)]))
		{
			coordinates = malloc(2 * sizeof(int));
			if (!coordinates)
				return (NULL);
			coordinates[0] = player_y / BLOCK_SIZE;
			coordinates[1] = player_x / BLOCK_SIZE;
			return (coordinates);
		}
		i++;
	}
	return (NULL);
}

void open_close_door(t_data *data)
{
	int		*coordinates;
	int		door_x;
	int		door_y;
	t_door	*door;

	coordinates = check_for_door(data->grid_map, data->player.pos.x, data->player.pos.y, data);
	if (coordinates)
	{
		door_x = coordinates[1];
		door_y = coordinates[0];
		free(coordinates);
		door = find_door(data->door_list, door_x *BLOCK_SIZE, door_y *BLOCK_SIZE);
		if (door)
		{
			if (door->type == DOOR)
				PlaySound(data->sound[S_DOOR]);
			else if (door->type == MET_DOOR)
				PlaySound(data->sound[S_MET_DOOR]);
			else if (door->type == STONE_DOOR)
				PlaySound(data->sound[S_STONE_DOOR]);
			if (door->state == CLOSED)
			{
				door->state = OPENING;
				door->time_opened = get_current_time();
			}
			else if (door->state == OPEN)
				door->state = CLOSING;
		}
	}
}

static int	has_10_seconds_passed(struct timeval start)
{
	struct timeval	now;
	long			seconds;
	long			microseconds;

	now = get_current_time();
	seconds = now.tv_sec - start.tv_sec;
	microseconds = now.tv_usec - start.tv_usec;
	if (microseconds < 0)
	{
		seconds -= 1;
		microseconds += 100000;
	}
	return (seconds >= 5);
}

int player_inside_door(t_data *data, t_door *door)
{
	int player_grid_x;
	int player_grid_y;

	player_grid_x = data->player.pos.x / BLOCK_SIZE;
	player_grid_y = data->player.pos.y / BLOCK_SIZE;
	if (door->grid_y == player_grid_y && door->grid_x == player_grid_x)
		return (1);
	else
		return (0);
}

void	update_doors(t_door *doors, t_data *data)
{
	while (doors)
	{
		if (doors->state == CLOSING)
		{
			if (!player_inside_door(data, doors))
			{
				doors->len += doors->move_spd;
				if (doors->len > BLOCK_SIZE)
					doors->state = CLOSED;
			}
		}
		else if (doors->state == OPENING)
		{
			doors->len -= doors->move_spd;
			if (doors->len < 0)
				doors->state = OPEN;
		}
		if (doors->state == OPEN)
		{
			if (has_10_seconds_passed(doors->time_opened))
			{
				if (!player_inside_door(data, doors))
					doors->state = CLOSING;
			}
		}
		doors = doors->next;
	}
}

t_door	*find_door(t_door *doors, int unit_x, int unit_y)
{
	while (doors)
	{
		if (doors->grid_x == unit_x / BLOCK_SIZE
			&& doors->grid_y == unit_y / BLOCK_SIZE)
		{
			return (doors);
		}
		doors = doors->next;
	}
	return (NULL);
}

t_door	*create_door(t_data *data, t_door **door_list, int grid_x, int grid_y)
{
	t_door	*new_door;
	t_door	*temp;

	new_door = malloc(sizeof(t_door));
	if (!new_door)
		return (NULL);
	new_door->type = data->grid_map[grid_y][grid_x];
	new_door->state = CLOSED;
	new_door->len = BLOCK_SIZE;
	new_door->grid_x = grid_x;
	new_door->grid_y = grid_y;
	new_door->next = NULL;
	new_door->move_spd = BLOCK_SIZE / 64;
	temp = *door_list;
	while (temp && temp->next)
		temp = temp->next;
	if (!temp)
		*door_list = new_door;
	else if (!temp->next)
		temp->next = new_door;
	return (new_door);
}
