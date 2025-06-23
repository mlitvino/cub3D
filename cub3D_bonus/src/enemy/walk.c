#include "cub3D.h"

/*void update_enemies(t_data *data, t_sprite *sprite, t_point player_pos, float time_elapsed)
{
    static float path_timer;
    const float path_update_interval;

	path_update_interval = 0.5f
	path_timer = 0.0f;
    path_timer += time_elapsed;
    if (sprite->path == NULL || path_timer >= path_update_interval)
    {
        if (sprite->path)
            free_path(sprite->path);
        sprite->path = bfs_find_path(data->grid_map, data, sprite->pos, player_pos);
        sprite->last_player_pos = player_pos;
        path_timer = 0.0f;
    }
}*/

void	update_wolf(t_data *data)
{
	t_sprite *sprite;

	sprite = data->sprite_list;

	while(sprite)
	{
		if (sprite->type == WOLF)
		{
			if (has_line_of_sight(sprite, &data->player, data->unit_map) && sprite->dist_player < 100) //check what distance makes sense
			{
				if (sprite->path)
				{
					free_path(sprite->path);
					sprite->path = NULL; //needs to be set to NULL in init sprite !!!
				}
				sprite->path = bfs_find_path(data->grid_map, data, sprite->pos, data->player.pos);
				if (sprite->path)
                    //printf("got path\n");
					move_to_goal(data);
			}
		}
		sprite = sprite->next;
	}
}


void move_to_goal(t_data *data, t_sprite *sprite, float speed)
{
    if (!sprite->path || !sprite->path->parent)
    {
        // No path or already at goal
        if (sprite->path)
        {
            free_path(sprite->path);
            sprite->path = NULL;
        }
        return ;
    }

    t_path *next_step = sprite->path;

    // Find the next node after the enemy’s current tile position
    while (next_step->parent && !(next_step->parent->pos.x == (int)sprite->pos.x && next_step->parent->pos.y == (int)sprite->pos.y))
    {
        next_step = next_step->parent;
    }

    // Calculate direction vector from current position to next path node
    float target_x = next_step->pos.x;
    float target_y = next_step->pos.y;

    float dx = target_x - sprite->pos.x;
    float dy = target_y - sprite->pos.y;
	float attack_range = 2.0f * player->radius; // Define attack range

	// Calculate distance between enemy and player
	float dx_player = player->pos.x - sprite->pos.x;
	float dy_player = player->pos.y - sprite->pos.y;
	float dist_to_player = sqrtf(dx_player * dx_player + dy_player * dy_player);

    float dist = sqrtf(dx * dx + dy * dy);

	if (dist_to_player <= attack_range)
	{
    	enemy_attack_player(sprite, data->player); //need to implement
    	sprite->path = NULL;
    	return ;
	}
    if (dist < 0.01f)
    {
        // Reached the next node tile, update path pointer
        sprite->pos.x = target_x;
        sprite->pos.y = target_y;
        sprite->path = next_step;

        // If no more parents, reached goal
        if (!sprite->path->parent)
        {
            free_path(sprite->path);
            sprite->path = NULL;
        }
    }
    else
    {
        // Move towards the next tile proportionally to speed
        sprite->pos.x += speed * (dx / dist);
        sprite->pos.y += speed * (dy / dist);
    }
}