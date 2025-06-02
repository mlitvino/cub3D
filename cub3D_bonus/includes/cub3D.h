/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:53:29 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/02 16:14:51 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42_Int.h"
# include "libft.h"
# include <errno.h>
# include <math.h>
# include <stdio.h>

# define BPP sizeof(int32_t)

# define WIN_W 1920
# define WIN_H 1080

# define FOV 60
# define BLOCK_SIZE 64
# define TEST_MAPX 7
# define TEST_MAPY 8

# define EMPTY 0
# define WALL 1
# define PLAYER 3
# define WOLF 'B' // BEAST, W - taken by player's char in subject
# define CANDLE 'C'

# define DOOR 'D'
# define CLOSED 1
# define CLOSING 2
# define OPEN 3
# define OPENING 4

# define VERTICAL 0
# define HORIZONT 1

# define ISNORTH(a) (a < 180)
# define ISSOUTH(a) (a > 180)
# define ISWEST(a) (90 < a && a < 270)
# define ISEAST(a) (270 < a || a < 90)

// Movement
# define DEG_TO_RAD(a) ((a)*M_PI / 180.0)

typedef enum e_texture
{
	NORTH,
	EAST,
	WEST,
	SOUTH,
	DOOR_TEX,
	WOLF_STAY,
	MAX_TEX
}	t_texture;

typedef struct s_data	t_data;

//------------------------------TEST----------------------------------
# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

//------------------------------Graphic----------------------------------

typedef struct s_dpoint
{
	double		x;
	double		y;
	double		h;

}				t_dpoint;

typedef struct s_point
{
	int			x;
	int			y;
	int			height;
	int			inval;

}				t_point;

typedef struct s_rgbt
{
	int			r;
	int			g;
	int			b;
	int			t;
	int			rgbt;

}				t_rgbt;

typedef struct s_project
{
	/*
		change in resize win case
	*/
	int			width;
	int			height;
	int			dist;
	t_point		center;

}				t_project;

typedef struct s_wall
{
	t_point		pos;
	int			dist;
	int			type;
	int			door_len;

	int			h;
	int			top;

	int			img_x;
	int			img_y;
	int			img_i;
	mlx_image_t	*img;

}				t_wall;

typedef struct s_door
{
	int				state;
	int				len;
	int				grid_x;
	int				grid_y;
	int				move_spd;
	int				direct;

	struct s_door	*next;

}					t_door;

typedef struct s_sprite
{
	mlx_image_t		*cur_img;
	int				tex_cur_img;
	mlx_image_t		**tex_imgs;

	int				hitbox_radius;
	t_point			pos;

	int				move_spd;
	int				turn_spd;

	int				img_x;
	int				img_y;
	int				img_i;

	int				walkable;// is needed?
	int				type;// ENEMY, OBJECT, is needed?
	int				dist;

	struct s_sprite	*next;

}	t_sprite;

typedef struct s_raycast
{
	t_data		*data;
	t_project	*plane;
	mlx_image_t	*scr_img;
	char		**unit_map;
	t_door		*door_list;
	int			rays_dist[WIN_W];

	int			flor_rgbt;
	int			ceil_rgbt;

	int			view_angle;
	t_point		char_pos;

	mlx_image_t	*wall_img;
	int			tex_x;

	double		dx;
	double		dy;
	int			axis;

	t_wall		hor_wall;
	t_wall		ver_wall;
	t_wall		wall;

	int			img_indx;
	double		ray_angle;
	int			cur_ray;
	double		beta;

	int			tex_indx;

	int			sprite_count;

}				t_raycast;

//-------------------------------GAME------------------------------------

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
	int			esc;

}				t_keys;

typedef struct s_pov
{
	t_point		view_pos;
	int			view_angl;
	int			fov;

}				t_pov;

typedef struct s_char
{
	t_data		*data;

	t_pov		pov;
	double		height;

	int			hitbox_radius;
	t_point		pos;

	int			move_spd;
	int			turn_spd;

}				t_char;

//-------------------------------GENERAL------------------------------------

typedef struct s_mlx
{
	mlx_t				*mlx_ptr;

	mlx_image_t			*scr_img;

	mlx_texture_t		*textrs[MAX_TEX];
	mlx_image_t			*textrs_img[MAX_TEX];

}						t_mlx;

typedef struct s_data
{
	t_mlx				mlx_data;

	char				grid_map[TEST_MAPY][TEST_MAPX];
	char				**unit_map;
	int					map_h;
	int					map_w;

	t_door				*door_list;
	t_sprite			*sprite_list;

	t_char				player;
	t_keys				keys;

	t_project			plane;
	int					rays_count;
	double				rays_angle;
	t_rgbt				flor_rgb;
	t_rgbt				ceil_rgb;

}						t_data;

//-------------------------------RAYCASTING------------------------------------
// helper.c
void		calc_norm_dist(t_raycast *raycast);
void		select_tex(t_raycast *raycast, t_wall *wall, int axis_flag);
t_raycast	init_raycast(t_data *data, t_char *player);
void		fill_ray_info(t_raycast *raycast);

// door.c
void		update_doors(t_door *doors);
t_door		*find_door(t_door *doors, int unit_x, int unit_y);
t_door		*create_door(t_door **doors_list, int grid_x, int grid_y);

// sprite.c
t_sprite	*create_sprite(t_data *data, int type, int grid_x, int grid_y);

// draw.c
void		map_wall(t_raycast *raycast, int y, int wall_h, int wall_top);
void		render_col(t_raycast *raycast, t_wall *wall,
				int wall_dist, int tex_indx);

// raycast.c
void		compre_dist(t_raycast *raycast, t_wall *hor_wall,
				t_wall *ver_wall);
void		cast_ray(t_raycast *raycast, double ray_angl);
void		raycast(t_data *data);

// find_wall_utils.c
bool		check_hit(t_raycast *raycast, t_wall *wall, int axis_flag);
bool		is_on_map(t_data *data, t_point *p);

// find_wall.c
void		init_wall(t_point char_pos, t_dpoint *temp,
				double ray_angl, int axis_flag);
void		adjust_wall(t_raycast *raycast, t_dpoint *temp);
void		init_delta(t_raycast *raycast, int axis_flag);
void		norm_fract(t_dpoint *temp, t_wall *wall, int axis_flag,
				double ray_angl);
bool		find_wall(t_raycast *raycast, t_wall *wall, int axis_flag);

// utils.c
double		deg_rad(double deg);
double		calc_dist(t_point p1, t_point p2);
uint32_t	extract_rgba(uint8_t *raw);

//-------------------------------MOVEMENT------------------------------------
void		key_event_handler(mlx_key_data_t keydata, void *param);
void		move_player(t_char *player, double angle_offset);
int			check_for_wall_collision(t_char *player, double new_x,
				double new_y);
void		rotate_player_right(t_char *player);
void		rotate_player_left(t_char *player);

//-------------------------------GENERAL------------------------------------

// clean.c
void		clean_map(t_data *data);
void		clean_mlx(t_data *data);
void		clean_all(t_data *data);

// init.c
void		init_grid_map(t_data *data);
void		init_unit_map(t_data *data);
void		init_maps(t_data *data);
void		init_mlx(t_data *data);
void		init_data(t_data *data);

// debug.c
void		show_sprites(t_sprite **sprite_array, t_sprite *sprite_list);
void		show_doors(t_door *list);
void		show_char_pos(t_data *data, t_char *chr);
void		show_unit_map(t_data *data);
void		show_redline(t_data *data);

#endif
