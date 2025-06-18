#include "cub3D.h"


static void	set_key_flag(t_keys *k, mlx_key_data_t keydata, int value)
{
	if (keydata.key == 'W')
        k->w = value;
	else if (keydata.key == MLX_KEY_A)
        k->a = value;
	else if (keydata.key == MLX_KEY_S)
        k->s = value;
	else if (keydata.key == MLX_KEY_D)
        k->d = value;
	else if (keydata.key == MLX_KEY_LEFT)
        k->left = value;
	else if (keydata.key == MLX_KEY_RIGHT)
        k->right = value;
	else if (keydata.key == MLX_KEY_ESCAPE)
        k->esc = value;
}

void	change_sprite_state(t_data *data, int type, int new_state)
{
	t_sprite *sprite;

	sprite = data->sprite_list;
	while (sprite)
	{
		if (sprite->type == type)
		{
			sprite->state = new_state;
			sprite->cur_img = sprite->tex_imgs[new_state];
		}
		sprite = sprite->next;
	}
}

void	key_event_handler(mlx_key_data_t keydata, void *param)
{
	t_data *data = (t_data *)param;

	if (keydata.key == 'R')
	{
		data->plane.center.y += 111;
		printf("new plane y %d\n", data->plane.center.y);
		PlaySound(data->test3);
	}
	else if (keydata.key == 'T')
	{
		data->plane.center.y -= 114;
		printf("new plane y %d\n", data->plane.center.y);
	}
	if (keydata.key == '1')
		change_sprite_state(data, WOLF, WOLF_STAY);
	else if (keydata.key == '2')
		change_sprite_state(data, WOLF, WOLF_WALK1);
	else if (keydata.key == '3')
		change_sprite_state(data, WOLF, WOLF_WALK2);
	else if (keydata.key == '4')
		change_sprite_state(data, WOLF, WOLF_ATTCK);

	if (keydata.key == '5')
		change_sprite_state(data, STATUE, STATUE_GREY);
	else if (keydata.key == '6')
		change_sprite_state(data, STATUE, STATUE_RED);
	else if (keydata.key == '7')
	{
		// data->mlx_data.textrs_img[CROSSBOW1]->instances[0].x -= 100;
		// data->mlx_data.textrs_img[CROSSBOW1]->instances[0].y -= 100;
		mlx_set_instance_depth(&data->mlx_data.textrs_img[CROSSBOW1]->instances[data->test1], 3);
		mlx_set_instance_depth(&data->mlx_data.textrs_img[CROSSBOW2]->instances[data->test2], 0);
		//data->player.facing_statue = data->sprite_list;
	}
	else if (keydata.key == '8')
	{
		// data->mlx_data.textrs_img[CROSSBOW1]->instances[0].x += 100;
		// data->mlx_data.textrs_img[CROSSBOW1]->instances[0].y += 100;
		mlx_set_instance_depth(&data->mlx_data.textrs_img[CROSSBOW1]->instances[data->test1], 0);
		mlx_set_instance_depth(&data->mlx_data.textrs_img[CROSSBOW2]->instances[data->test2], 3);
		// data->player.facing_statue = NULL;
	}


	if (keydata.key == 'Q')
	{
		t_sprite *enemy = data->player.facing_enemy;
		if (enemy)
		{
			printf("type_name: %s\n", enemy->type == WOLF ? "WOLF" : enemy->type == STATUE ? "STATUE" : "UNKNOWN");
			printf("x %d, y %d\n", enemy->pos.x, enemy->pos.y);
		}
		else
		{
			printf("Enemy is not in center of screen\n");
		}
	}
	if (keydata.key == MLX_KEY_SPACE /*&& is_center_door */)
	{
		open_door(data);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		clean_all(data);
		return ;
	}
	if (keydata.action == MLX_PRESS /*|| keydata.action == MLX_REPEAT*/)
		set_key_flag(&data->keys, keydata, 1);
	else if (keydata.action == MLX_RELEASE)
		set_key_flag(&data->keys, keydata, 0);
}
