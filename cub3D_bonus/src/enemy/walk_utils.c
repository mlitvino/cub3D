#include "cub3D.h"

static int	no_path_return(t_sprite *sprite)
{
	sprite->path = NULL;
	return (0);
}

static void	switch_img(t_sprite *sprite)
{
	if (sprite->cur_img == sprite->tex_imgs[WOLF_STAY])
		sprite->cur_img = sprite->tex_imgs[WOLF_WALK1];
	if (++sprite->move_rate >= 12)
	{
		sprite->move_rate = 0;
		if (sprite->cur_img == sprite->tex_imgs[WOLF_ATTCK])
			sprite->cur_img = sprite->tex_imgs[WOLF_WALK1];
		if (sprite->cur_img == sprite->tex_imgs[WOLF_WALK1])
			sprite->cur_img = sprite->tex_imgs[WOLF_WALK2];
		else if (sprite->cur_img == sprite->tex_imgs[WOLF_WALK2])
			sprite->cur_img = sprite->tex_imgs[WOLF_WALK1];
	}
}

static void	set_new_pos(t_data *data, t_sprite *sprite,
	float new_x, float new_y)
{
	if (can_move_wall_enemy(sprite, new_x, sprite->pos.y, data)
		&& can_move_enemy_collision(sprite, new_x, sprite->pos.y, data))
		sprite->pos.x = new_x;
	if (can_move_wall_enemy(sprite, sprite->pos.x, new_y, data)
		&& can_move_enemy_collision(sprite, sprite->pos.x, new_y, data))
		sprite->pos.y = new_y;
}

static void	check_end_of_path(t_sprite *sprite)
{
	t_path *tmp;

	tmp = sprite->path;

	if ((sprite->pos.x == sprite->last_seen.x
				&& sprite->pos.y == sprite->last_seen.y))
			sprite->has_player_in_sight = 0;
	while (tmp)
	{
		if (!tmp->parent)
		{
			if (sprite->pos.x / BLOCK_SIZE == tmp->pos.x && sprite->pos.y / BLOCK_SIZE  == tmp->pos.y)
			{
				sprite->path = NULL;
			}
		}
		tmp = tmp->parent;
	}
}

static int	move_wolf(t_sprite *sprite, t_data *data, int x, int y)
{
	float	new_x;
	float	new_y;
	float	dx;
	float	dy;
	float	dist;

	dx = x - sprite->pos.x;
	dy = y - sprite->pos.y;
	dist = sqrtf(dx * dx + dy * dy);
	if (sprite->dist <= sprite->attack_range)
	{
		sprite->moved = 0;
		return (no_path_return(sprite));
	}
	else
	{
		if (IsSoundPlaying(data->sound[S_WOLF_CHASE]) == false)
			PlaySound(data->sound[S_WOLF_CHASE]);
		new_x = sprite->pos.x + sprite->move_spd * (dx / dist);
		new_y = sprite->pos.y + sprite->move_spd * (dy / dist);
		sprite->moved++;
		switch_img(sprite);
		set_new_pos(data, sprite, new_x, new_y);
		check_end_of_path(sprite);
	}
	return (1);
}

void	move_to_goal(t_sprite *sprite, t_data *data)
{
	t_path	*next_step;
	float	target_x;
	float	target_y;

	next_step = sprite->path;
	if (!sprite->path)
	{
		no_path(sprite);
		return ;
	}
	while (next_step->parent && !(next_step->parent->pos.x == (int)sprite->pos.x
			&& next_step->parent->pos.y == (int)sprite->pos.y))
	{
		next_step = next_step->parent;
	}
	target_x = next_step->pos.x * BLOCK_SIZE + BLOCK_SIZE / 2;
	target_y = next_step->pos.y * BLOCK_SIZE + BLOCK_SIZE / 2;
	if (!move_wolf(sprite, data, target_x, target_y))
	{
		return ;
	}
}
