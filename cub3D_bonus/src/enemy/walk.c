#include "cub3D.h"

static void print_path(t_path *path)
{
	int	step;

	step = 0;
	if (!path)
	{
		printf("Path is NULL\n");
		return ;
	}
	printf("---- PATH START ----\n");
	while (path)
	{
		printf("Step %d: Tile (%d, %d)\n", step++, path->pos.x, path->pos.y);
		path = path->parent;
	}
	printf("---- PATH END ----\n");
}
static void	attack_player(t_sprite *sprite)
{
	//printf("dist: %d, range: %d\n", sprite->dist, sprite->attack_range);
	if (sprite->dist <= sprite->attack_range)
	{
		//printf("%d\n", sprite->move_rate);
		if (++sprite->move_rate >= 50 || sprite->moved > 5)
		{
			//printf("moved: %d\n", sprite->moved);
			if (sprite->move_rate >= 50)
				sprite->move_rate = 0;
			if (sprite->cur_img == sprite->tex_imgs[WOLF_WALK1]
				|| sprite->cur_img == sprite->tex_imgs[WOLF_WALK2])
				sprite->cur_img = sprite->tex_imgs[WOLF_ATTCK];
			else if (sprite->cur_img == sprite->tex_imgs[WOLF_ATTCK])
				sprite->cur_img = sprite->tex_imgs[WOLF_WALK2];
			else if (sprite->cur_img == sprite->tex_imgs[WOLF_WALK2])
				sprite->cur_img = sprite->tex_imgs[WOLF_ATTCK];
		}
		if (sprite->path)
		{
			free_path(sprite->path);
			sprite->path = NULL;
		}
		return ;
	}
}

static void	wolf_action(t_sprite *sprite, t_data *data)
{
	attack_player(sprite);
	if (has_line_of_sight(sprite, &data->player, data->unit_map)
		&& sprite->dist < 10 * BLOCK_SIZE)
	{
		//printf("called1\n");
		if (sprite->path)
		{
			free_path(sprite->path);
			sprite->path = NULL;
		}
		sprite->last_seen = data->player.pos;
		sprite->has_player_in_sight = 1;
		sprite->path = bfs_find_path(data, sprite->pos, data->player.pos);
		if (sprite->path)
		{
			move_to_goal(sprite, data);
		}
	}
	else if (sprite->has_player_in_sight)
	{
		//printf("called2\n");
		t_path *tmp = sprite->path;
		t_path *prev = NULL;
		t_door *door;

		while (tmp && sprite->has_player_in_sight)
		{
			//printf("called\n");
			if (tmp->parent)
			{
				int x = tmp->parent->pos.x;
				int y = tmp->parent->pos.y;
				if (data->grid_map[y][x] == 'D')
				{
					door = find_door(data->door_list, x * BLOCK_SIZE, y * BLOCK_SIZE);
					if (door && door->state != OPEN)
					{
						if (prev)
						{
							tmp->parent = NULL;
						}
						else
						{
							sprite->path = NULL;
						}
					}
				}
			}
			prev = tmp;
			tmp = tmp->parent;
		}
		if (sprite->path)
		{
			//print_path(sprite->path);
			move_to_goal(sprite, data);
		}
		//sprite->path = bfs_find_path(data, sprite->pos, sprite->last_seen);
		//if (sprite->path)
			//move_to_goal(sprite, data);
		else
			sprite->has_player_in_sight = 0;
	}
	else
	{
		//printf("called3\n");
		sprite->cur_img = sprite->tex_imgs[WOLF_STAY];
	}
}

int	can_move_enemy_collision(t_sprite *sprite, float new_x, float new_y,
		t_data *data)
{
	t_sprite	*other;
	float		dx;
	float		dy;
	float		dist_squared;
	float		min_dist;

	other = data->sprite_list;
	while (other)
	{
		if (other != sprite)
		{
			dx = other->pos.x - new_x;
			dy = other->pos.y - new_y;
			dist_squared = dx * dx + dy * dy;
			min_dist = sprite->hitbox_radius / 4 + other->hitbox_radius / 4;
			if (dist_squared < (min_dist * min_dist))
				return (0);
		}
		other = other->next;
	}
	return (1);
}

int	can_move_wall_enemy(t_sprite *sprite, float new_x, float new_y,
		t_data *data)
{
	int		cell_top;
	int		cell_bottom;
	int		cell_left;
	int		cell_right;
	char	**unit_map;

	unit_map = data->unit_map;
	cell_top = floor((new_y - (sprite->hitbox_radius / 4)));
	cell_bottom = floor((new_y + (sprite->hitbox_radius / 4)));
	cell_left = floor((new_x - (sprite->hitbox_radius / 4)));
	cell_right = floor((new_x + (sprite->hitbox_radius / 4)));
	if (cell_top < 0 || cell_left < 0 || cell_bottom >= data->map_h * BLOCK_SIZE
		|| cell_right >= data->map_w * BLOCK_SIZE)
	{
		return (0);
	}
	if (unit_map[cell_top][cell_left] == WALL
		|| unit_map[cell_top][cell_right] == WALL
		|| unit_map[cell_bottom][cell_left] == WALL
		|| unit_map[cell_bottom][cell_right] == WALL)
	{
		return (0);
	}
	return (1);
}

void	update_wolf(t_data *data)
{
	t_sprite	*sprite;

	sprite = data->sprite_list;
	while (sprite)
	{
		if (sprite->type == WOLF /*&& sprite->state != DIED*/)
		{
			wolf_action(sprite, data);
		}
		sprite = sprite->next;
	}
}
