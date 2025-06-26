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

/*static void print_path(t_path *path)
{
    int step = 0;

    if (!path)
    {
        printf("Path is NULL\n");
        return;
    }

    printf("---- PATH START ----\n");

    while (path)
    {
        printf("Step %d: Tile (%d, %d)\n", step++, path->pos.x, path->pos.y);
        path = path->parent;
    }

    printf("---- PATH END ----\n");
}*/

void    attack_player(t_sprite *sprite)
{
    if (sprite->dist <= sprite->attack_range)
	{
    	//enemy_attack_player(sprite, data->player); //need to implement
        if (++sprite->move_rate >= 50)
        {
            sprite->move_rate = 0;
            if (sprite->cur_img == sprite->tex_imgs[WOLF_WALK1] || sprite->cur_img == sprite->tex_imgs[WOLF_WALK2])
                sprite->cur_img = sprite->tex_imgs[WOLF_ATTCK];
            else if (sprite->cur_img == sprite->tex_imgs[WOLF_ATTCK])
                sprite->cur_img = sprite->tex_imgs[WOLF_WALK2];
            else if (sprite->cur_img == sprite->tex_imgs[WOLF_WALK2])
                sprite->cur_img = sprite->tex_imgs[WOLF_ATTCK];
        }
    	sprite->path = NULL;
    	return ;
	}
}
void	update_wolf(t_data *data)
{
	t_sprite *sprite;

	sprite = data->sprite_list;

	while(sprite)
	{
		if (sprite->type == WOLF)
		{
            //printf("distance: %d\n", sprite->dist);
            attack_player(sprite);
            if (sprite->path)
			{
				free_path(sprite->path);
				sprite->path = NULL;
			}
			if (has_line_of_sight(sprite, &data->player, data->unit_map)  && sprite->dist < 7 * BLOCK_SIZE) //check what distance makes sense
			{
                //printf("sprite posx : %d sprite posy: %d", sprite->pos.x, sprite->pos.y);
				sprite->path = bfs_find_path(data, sprite->pos, data->player.pos);
				if (sprite->path)
                {
                    //printf("got path\n");
                    //print_path(sprite->path);
					move_to_goal(sprite, sprite->move_spd);
                }
			}
            else
                sprite->cur_img = sprite->tex_imgs[WOLF_STAY];

		}
		sprite = sprite->next;
	}
}

void move_to_goal(t_sprite *sprite, float speed)
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
    float target_x = next_step->pos.x * BLOCK_SIZE + BLOCK_SIZE / 2;
    float target_y = next_step->pos.y * BLOCK_SIZE + BLOCK_SIZE / 2;

    float dx = target_x - sprite->pos.x;
    float dy = target_y - sprite->pos.y;
	//float attack_range = 4.0f * data->player.hitbox_radius;
    float dist = sqrtf(dx * dx + dy * dy);

    //printf("dist: %d range: %f\n", sprite->dist, attack_range);
	if (sprite->dist <= sprite->attack_range)
	{
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
       
        if (sprite->cur_img == sprite->tex_imgs[WOLF_STAY])
            sprite->cur_img = sprite->tex_imgs[WOLF_WALK1];
        if (++sprite->move_rate >= 12)
        {
            sprite->move_rate = 0;
            if (sprite->cur_img == sprite->tex_imgs[WOLF_ATTCK])
                sprite->cur_img = sprite->tex_imgs[WOLF_STAY];
            if (sprite->cur_img == sprite->tex_imgs[WOLF_WALK1])
                sprite->cur_img = sprite->tex_imgs[WOLF_WALK2];
            else if (sprite->cur_img == sprite->tex_imgs[WOLF_WALK2])
                sprite->cur_img = sprite->tex_imgs[WOLF_WALK1];
        }
        // Move towards the next tile proportionally to speed
        sprite->pos.x += speed * (dx / dist);
        sprite->pos.y += speed * (dy / dist);
    }
}