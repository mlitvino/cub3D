
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:53:29 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/11 13:48:31 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "raylib.h"

# include "MLX42/MLX42_Int.h"

# include "libft.h"
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/time.h>
# include <pthread.h>

# define BPP sizeof(int32_t)

# define WIN_W 1280
# define WIN_H 720

# define MAX_THRD 6

# define FOV 60
# define BLOCK_SIZE 512
# define TEST_MAPX 50
# define TEST_MAPY 14

# define SCALE 20
# define ICON_SIZE 8
# define ICON_BASE 3
# define MODIF_BRIGHT 4

# define STATUE_MAX_VIS 2

# define EMPTY '0'
# define WALL '1'

# define STATUE 'C'
# define FLOOR 'F'


# define WOLF 'B'

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
	FLOOR_TEX,
	GROUND_TEX,
	CEIL_TEX,
	SKY_TEX,
	WOLF_STAY,
	WOLF_WALK1,
	WOLF_WALK2,
	WOLF_ATTCK,
	WOLF_DEAD,
	STATUE_GREY,
	STATUE_RED,
	STATUE_FACE,
	CROSSBOW1,
	CROSSBOW2,
	MAX_TEX
}	t_texture;

typedef enum e_audio
{
	MAX_AUDIO
}	t_audio;

typedef struct s_data		t_data;
typedef struct s_raycast	t_raycast;
typedef struct s_char		t_char;

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
	int			h;

}				t_point;

typedef struct s_rgbt
{
	int			r;
	int			g;
	int			b;
	int			t;
	uint32_t 	rgbt;

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

	struct timeval	time_opened;

	struct s_door	*next;

}					t_door;

typedef struct s_sprite
{
	mlx_image_t		*cur_img;
	int				state;
	mlx_image_t		**tex_imgs;

	int				hitbox_radius;
	t_point			pos;

	int				move_spd;
	int				turn_spd;

	int				walkable;
	int				type;
	int				dist;

	t_point			size;
	t_point			tex_p;

	int				height;
	int				width;
	int				top;
	int				left;
	double			angle;

	struct s_sprite	*next;

}	t_sprite;



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

	int			door_facing;
	t_pov		pov;
	double		height;

	int			hitbox_radius;
	t_sprite	*facing_enemy;
	t_sprite	*facing_statue;
	t_point		pos;

	int			move_spd;
	int			turn_spd;

}				t_char;

typedef struct s_raycast
{
	t_data		*data;
	t_project	*plane;
	mlx_image_t	*scr_img;
	char		**unit_map;
	t_door		*door_list;

	t_char		*player;

	int			thread_chunk;
	t_sprite	*thread_sprite;
	pthread_t	threads[MAX_THRD];
	int			thrd_i;

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

//-------------------------------GENERAL------------------------------------

typedef struct s_mlx
{
	mlx_t				*mlx_ptr;

	mlx_image_t			*scr_img;
	mlx_image_t			*minimap;

	char			**ceiling_colour;
	char			**floor_colour;
	char			*tex_path[MAX_TEX];
	mlx_texture_t	*textrs[MAX_TEX];
	mlx_image_t		*textrs_img[MAX_TEX];

}						t_mlx;

// typedef struct s_audio
// {
// 	Music	music;
// 	Sound	sound;
// }			t_audio;

typedef struct s_data
{
	t_mlx				mlx_data;

	char				**grid_map;
	char				**unit_map;
	char				**map_data;
	char				**work_map;
	int					line_count;
	int					map_h;
	int					map_w;

	t_door				*door_list;
	t_sprite			*sprite_list;

	t_char				player;
	t_keys				keys;

	t_project			plane;
	int					rays_count;
	int					rays_dist[WIN_W];
	double				rays_angle;
	t_rgbt				flor_rgb;
	t_rgbt				ceil_rgb;

	int					test1;
	int					test2;

	Sound				test3;

}						t_data;

//-------------------------------RAYCASTING------------------------------------
// thread.c
void	*thread_sprite(void *arg);
void	*thread_raycast(void *arg);
void	init_threads(t_raycast *raycast, void *(routine)(void *arg));

// helper.c
void		calc_norm_dist(t_raycast *raycast);
void		select_tex(t_raycast *raycast, t_wall *wall, int axis_flag);
t_raycast	*init_raycast(t_data *data, t_char *player, t_raycast *raycast);
void		fill_ray_info(t_raycast *raycast);

// door.c
void		update_doors(t_door *doors);
t_door		*find_door(t_door *doors, int unit_x, int unit_y);
t_door		*create_door(t_door **doors_list, int grid_x, int grid_y);

// sprite.c
void		sort_sprite_dist(t_raycast *raycast, t_sprite **sprite_array);
double		calc_angl_dif(t_raycast *raycast, t_sprite *srpite);
void		calc_sprite(t_raycast *raycast, t_sprite **sprites);
void		draw_sprite_pix(t_raycast *raycast, t_sprite *sprite, int x, int y);
void		draw_sprite(t_raycast *raycast, t_sprite *sprite);

// sprite_init.c
t_sprite	*create_sprite(t_data *data, int type, int grid_x, int grid_y);
t_sprite	**init_spite_array(t_raycast *raycast);

// draw.c
void		add_shadow(uint32_t *color, int *dist);
void		map_wall(t_raycast *raycast, int y, int wall_h, int wall_top);
void		render_col(t_raycast *raycast, t_wall *wall,
				int wall_dist, int tex_indx);

// raycast.c
void		compre_dist(t_raycast *raycast, t_wall *hor_wall,
				t_wall *ver_wall);
void		cast_ray(t_raycast *raycast, double ray_angl);
void		handle_sprites(t_raycast *raycast);
void		raycast(t_data *data);

// minimap_player.c
int			edge_function(t_point a, t_point b, t_point c);
bool		point_in_triangle(t_point p, t_point a, t_point b, t_point c);
void		norm_base(t_point *base_left, t_point *base_right, t_point *max, t_point *min);
void	fill_icon_with_color(mlx_image_t *minimap,
							t_point *tip, t_point *base_left, t_point *base_right);
void	draw_player(double view_angle, mlx_image_t *minimap, int mid_x, int mid_y);

// minimap_utils.c
void	init_d_step(t_point *p1, t_point *p2, t_point *d, t_point *step);
void	draw_line(mlx_image_t *img, t_point *p1, t_point *p2, int color);

// minimap.c
void	draw_background(mlx_image_t *minimap);
void	draw_obj(t_data *data, t_point *mid_img, mlx_image_t *minimap);
void	draw_minimap(t_data *data, mlx_image_t *minimap);


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

// audio.c
void		init_audio(t_data *data);

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
void		draw_aim_cross(mlx_image_t *scr_img);

//----------------------------------PARSING-----------------------------------------

//free error functions
int	return_invalid_element(void);
int error_exit(char * message);
char	**error_return(char *message);
int free_return(int *data);
int	perror_free_map(char **map);
char	**free_map(char **map, int fd);
void	free_colours_textures_strings(t_data *data);
int	error_free_return(char *message, t_data *data);
int	free_map_return(t_data *data);
int 	free_error_exit(char *line, char *colour);
char **perror_return(void);
int	perror_return_int(int *data);
char **perror_free(char **map_data, int fd);
int	perror_exit(char *line);
char	*perror_exit_null(void);

//utils
int	valid_end_of_string(int *i, int done, char *line, char *colour);
int	valid_colour_number(char *colour, int floor_ceiling, int rgb, t_data *data);
int valid_colours(t_data *data);
char *set_colour(char *line, int *i, int done);
int	set_rgb(int	floor_or_ceiling, char *line_trim, int *i, t_data *data);
int free_element_map(int *element, t_data *data);
int	create_temp_map(char **map, int *i, t_data *data);
int	is_identifier(char *line);
int	is_map_element(char *line, int *map_element, t_data *data);
int is_empty_line(char *line);
void	init_null(t_data *data);
int	fill_map(t_data *data, char **map_data, int fd);
int	valid_extension(const char *filename);
char **pad_map(char **map, int height, t_data *data);
void	set_angle(char angle, t_data *data);

int set_floor_colour(t_data * data, char *line_trim, int *i);
int set_ceiling_colour(t_data * data, char *line_trim, int *i);
int set_floor_ceiling(t_data *data, char *element, char *line);
char **read_file(char *filename, t_data *data);
int valid_map(t_data *data);
int is_valid_surrounding(char **map, int height, int width);
int	is_valid_data(char **map, t_data *data, int line_count);
int check_map_borders(char **map, int height);
int	longest_line(char **map, int height);
int	fill_padded_map(int height, t_data *data, char **padded_map, char **map);
int	last_line_no_newline(char *line);
int check_double_element_wall(int *map_element, char *element, char *line, t_data *data);
int	check_doors(char **map);

void handle_mouse_rotation(t_data *game);
void open_door(t_data *data);

#endif
