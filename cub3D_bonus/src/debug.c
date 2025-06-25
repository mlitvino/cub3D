/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 22:53:42 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/25 14:39:47 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	show_fps(void)
{
	static struct timeval	last = {0, 0};
	static int				frames = 0;
	struct timeval			now;
	double					elapsed;

	gettimeofday(&now, NULL);
	// Initialize last on first call
	if (last.tv_sec == 0 && last.tv_usec == 0)
	{
		last = now;
		return ;
	}
	frames++;
	elapsed = (now.tv_sec - last.tv_sec) + (now.tv_usec - last.tv_usec)
		/ 1000000.0;
	if (elapsed >= 1.0)
	{
		printf("FPS: %d\n", frames);
		frames = 0;
		last = now;
	}
}

// // void	show_sprites(t_sprite **sprite_array, t_sprite *sprite_list)
// // {
// // 	int i;
// // 	t_sprite *tmp;

// // 	ft_printf("==== SPRITES DEBUG ====\n");
// // 	if (sprite_array)
// // 	{
// // 		ft_printf("Sprite Array:\n");
// // 		i = 0;
// // 		while (sprite_array[i])
// // 		{
// // 			ft_printf("Sprite Array[%d]:\n", i);
// // 			ft_printf("  pos: x = %d, y = %d\n", sprite_array[i]->pos.x,
// 				sprite_array[i]->pos.y);
// // 			ft_printf("  hitbox_radius: %d\n", sprite_array[i]->hitbox_radius);
// // 			ft_printf("  tex_cur_img: %d\n", sprite_array[i]->tex_cur_img);
// // 			ft_printf("  move_spd: %d, turn_spd: %d\n",
// 				sprite_array[i]->move_spd, sprite_array[i]->turn_spd);
// // 			ft_printf("  img_x: %d, img_y: %d, img_i: %d\n",
// 				sprite_array[i]->img_x, sprite_array[i]->img_y,
// 				sprite_array[i]->img_i);
// // 			ft_printf("  walkable: %d, type: %d\n", sprite_array[i]->walkable,
// 				sprite_array[i]->type);
// // 			ft_printf("  dist: %d\n\n", sprite_array[i]->dist);
// // 			i++;
// // 		}
// // 	}
// // 	if (sprite_list)
// // 	{
// // 		ft_printf("Sprite Linked List:\n");
// // 		i = 0;
// // 		tmp = sprite_list;
// // 		while (tmp)
// // 		{
// // 			ft_printf("Sprite %d:\n", i);
// // 			ft_printf("  pos: x = %d, y = %d\n", tmp->pos.x, tmp->pos.y);
// // 			ft_printf("  hitbox_radius: %d\n", tmp->hitbox_radius);
// // 			ft_printf("  tex_cur_img: %d\n", tmp->tex_cur_img);
// // 			ft_printf("  move_spd: %d, turn_spd: %d\n", tmp->move_spd,
// 				tmp->turn_spd);
// // 			ft_printf("  img_x: %d, img_y: %d, img_i: %d\n", tmp->img_x,
// 				tmp->img_y, tmp->img_i);
// // 			ft_printf("  walkable: %d, type: %d\n", tmp->walkable, tmp->type);
// // 			ft_printf("  dist: %d\n\n", tmp->dist);
// // 			i++;
// // 			tmp = tmp->next;
// // 		}
// // 	}
// // 	ft_printf("==== END SPRITES DEBUG ====\n");
// // }

void	show_doors(t_door *list)
{
	ft_printf("---DOOR_START---\n");
	for (int i = 0; list; i++, list = list->next)
	{
		ft_printf("i: %d\n", i);
		if (list->state == CLOSED)
			ft_printf("state: CLOSED\n");
		if (list->state == OPEN)
			ft_printf("state: OPEN\n");
		if (list->state == CLOSING)
			ft_printf("state: CLOSING\n");
		if (list->state == OPENING)
			ft_printf("state: OPENING\n");
		ft_printf("len: %d\n", list->len);
		ft_printf("grid x %d, gid y %d\n", list->grid_x, list->grid_y);
		ft_printf("middle unit x %d, unit y %d\n", list->grid_x * BLOCK_SIZE
			/ 2, list->grid_y * BLOCK_SIZE / 2);
	}
	ft_printf("----DOOR_END----\n");
}

void	show_unit_map(t_data *data)
{
	for (int j = 0; j < data->map_h * BLOCK_SIZE; j++)
	{
		ft_printf("{");
		for (int i = 0; i < data->map_w * BLOCK_SIZE; i++)
		{
			// if (data->unit_map[j][i] == EMPTY)
			// {
			// 	ft_printf("%d ", data->unit_map[j][i]);
			// }
			// else if (data->unit_map[j][i] == WALL)
			// {
			// 	ft_printf("%s%d %s", GREEN, data->unit_map[j][i], RESET);
			// }
			// // else if (data->unit_map[j][i] == PLAYER)
			// // {
			// // 	ft_printf("%s%d %s", RED, data->unit_map[j][i], RESET);
			// // }
			// else if (data->unit_map[j][i] == DOOR)
			// {
			// 	ft_printf("%s%d %s", BLUE, data->unit_map[j][i], RESET);
			// }
		}
		ft_printf("}\n");
	}
}

void	show_char_pos(t_data *data, t_char *chr)
{
	(void)data;
	ft_printf("Char x: %d, y: %d\n", chr->pos.x, chr->pos.y);
}

void	show_redline(t_data *data)
{
	for (int y = 0; y < (int)data->mlx_data.scr_img->height; y++)
		mlx_put_pixel(data->mlx_data.scr_img, data->plane.center.x, y,
			0xFF0000FF);
}

void	draw_aim_cross(mlx_image_t *scr_img)
{
	for (int x = scr_img->width / 2 - 10; x < (int)scr_img->width / 2 + 10; x++)
		mlx_put_pixel(scr_img, x, scr_img->height / 2, 0xFF0000FF);
	for (int y = scr_img->height / 2 - 10; y < (int)scr_img->height / 2
		+ 10; y++)
		mlx_put_pixel(scr_img, scr_img->width / 2, y, 0xFF0000FF);
}

void	draw_menu_but_grid(t_data *data, int state)
{
	t_point	main_but = data->keys.main_button;
	t_point	pause_but = data->keys.pause_button;
	mlx_image_t	*menu = data->mlx_data.textrs_img[MAIN_MENU];
	// main
	if (state == MAIN_MENU)
	{
		// left_ver line
		for (uint32_t y = 0; y < menu->height; y++)
			mlx_put_pixel(menu, main_but.x, y, 0xFF0000FF);
		// right_ver line
		for (uint32_t y = 0; y < menu->height; y++)
			mlx_put_pixel(menu, main_but.x + BUTTON_DX, y, 0xFF0000FF);
		// 1_but_hor_1 line
		for (uint32_t x = 0; x < menu->width; x++)
			mlx_put_pixel(menu, x, main_but.y , 0xFF0000FF);
		// 1_but_hor_2 line
		for (uint32_t x = 0; x < menu->width; x++)
			mlx_put_pixel(menu, x, main_but.y + BUTTON_DY, 0xFF0000FF);

		// 2_but_hor_1 line
		for (uint32_t x = 0; x < menu->width; x++)
			mlx_put_pixel(menu, x, main_but.y + BUTTON_DY + BUTTON_DY2, 0xFF0000FF);
		// 2_but_hor_2 line
		for (uint32_t x = 0; x < menu->width; x++)
			mlx_put_pixel(menu, x, main_but.y + BUTTON_DY * 2 + BUTTON_DY2, 0xFF0000FF);

		// 3_but_hor_1 line
		for (uint32_t x = 0; x < menu->width; x++)
			mlx_put_pixel(menu, x, main_but.y + (BUTTON_DY + BUTTON_DY2) * 2, 0xFF0000FF);
		// 3_but_hor_2 line
		for (uint32_t x = 0; x < menu->width; x++)
			mlx_put_pixel(menu, x, main_but.y + (BUTTON_DY + BUTTON_DY2) * 2 + BUTTON_DY, 0xFF0000FF);
	}
	// pause
	else if (state == PAUSE || state == WIN || state == DEATH)
	{
		mlx_image_t	*pause = data->mlx_data.textrs_img[state];
		// left_ver line
		for (uint32_t y = 0; y < pause->height; y++)
			mlx_put_pixel(pause, pause_but.x, y, 0xFF0000FF);
		// right_ver line
		for (uint32_t y = 0; y < pause->height; y++)
			mlx_put_pixel(pause, pause_but.x + BUTTON_DX, y, 0xFF0000FF);
		// 1_but_hor_1 line
		for (uint32_t x = 0; x < pause->width; x++)
			mlx_put_pixel(pause, x, pause_but.y , 0xFF0000FF);
		// 1_but_hor_2 line
		for (uint32_t x = 0; x < pause->width; x++)
			mlx_put_pixel(pause, x, pause_but.y + BUTTON_DY, 0xFF0000FF);

		// 2_but_hor_1 line
		for (uint32_t x = 0; x < pause->width; x++)
			mlx_put_pixel(pause, x, pause_but.y + BUTTON_DY + BUTTON_DY2, 0xFF0000FF);
		// 2_but_hor_2 line
		for (uint32_t x = 0; x < pause->width; x++)
			mlx_put_pixel(pause, x, pause_but.y + BUTTON_DY * 2 + BUTTON_DY2, 0xFF0000FF);

		// 3_but_hor_1 line
		for (uint32_t x = 0; x < pause->width; x++)
			mlx_put_pixel(pause, x, pause_but.y + (BUTTON_DY + BUTTON_DY2) * 2, 0xFF0000FF);
		// 3_but_hor_2 line
		for (uint32_t x = 0; x < pause->width; x++)
			mlx_put_pixel(pause, x, pause_but.y + (BUTTON_DY + BUTTON_DY2) * 2 + BUTTON_DY, 0xFF0000FF);
	}
}
