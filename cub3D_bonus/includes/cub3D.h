/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:53:29 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/22 20:00:57 by mlitvino         ###   ########.fr       */
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

# define WIN_W 1280
# define WIN_H 720

# define MINIMAP_W (WIN_W / 5)
# define MINIMAP_H (WIN_W / 5)

# define SKY_W 1440
# define SKY_H 5000

# define MAIN_BUTTON (t_point){1475,535,0}
# define PAUSE_BUTTON (t_point){745,385,0}
# define BUTTON_DX 390
# define BUTTON_DY 120
# define BUTTON_DY2 165

# define MAX_THRD 6

# define FOV 60
# define BLOCK_SIZE 512
# define ANGLE_PRES 100

# define SCALE 40
# define ICON_SIZE 16
# define ICON_BASE 6

# define MODIF_BRIGHT 2

# define STATUE_MAX_VIS 4
# define W_STATUE_VIS_DEC 25
# define H_STATUE_VIS_DEC 3

# define START 100
# define EXIT 101

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
	CEILING_TEX,
	SKY_TEX,
	WOLF_STAY,
	WOLF_WALK1,
	WOLF_WALK2,
	WOLF_ATTCK,
	WOLF_DEAD,
	STATUE_GREY,
	STATUE_RED,
	MAIN_MENU,
	PAUSE,
	DEATH,
	CONTROLS,
	STATUE_FACE,
	CROSSBOW1,
	CROSSBOW2,
	MAX_TEX
}	t_texture;

# define S_DOOR_PATH "audio/wood_door.mp3"
# define S_SHOT_PATH "audio/shot_reloading.mp3"
# define S_RELOADING_PATH "audio/reloading.mp3"

# define M_STORM_PATH "audio/storm.mp3"
# define M_FOREST_PATH "audio/forest.mp3"
# define M_PLAYER_STEP_PATH "audio/player_step.mp3"
# define M_WOLF_STEP_PATH "audio/wolf_step.mp3"


# define GREEN_COL 0x00d118ff
# define ORANGE_COL 0xeb6437ff

typedef enum e_music
{
	M_PLAYER_STEP,
	M_WOLF_STEP,
	M_FOREST,
	M_STORM,
	MAX_MUSIC
}	e_music;

typedef enum e_sound
{
	S_SHOT,
	S_RELOADING,
	S_DOOR,
	MAX_SOUND
}	e_sound;

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
	t_point		tex_pos;

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
	int			tab;

}				t_keys;

typedef struct s_pov
{
	t_point		view_pos;
	double		view_angl;
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
	t_dpoint		pos;

	int			move_spd;
	int			turn_spd;

}				t_char;

typedef struct s_table
{
	float	sin;
	float	cos;
	float	tan;
	float	beta;
}			t_table;

typedef struct s_raycast
{
	t_data		*data;
	t_project	*plane;
	mlx_image_t	*scr_img;
	char		**unit_map;
	t_door		*door_list;

	int			thread_chunk;
	t_sprite	*thread_sprite;
	pthread_t	threads[MAX_THRD];
	int			thrd_i;

	int			flor_rgbt;
	int			ceil_rgbt;

	t_char		*player;

	double		view_angle;
	t_point		char_pos;

	double		dx;
	double		dy;
	int			axis;

	t_wall		hor_wall;
	t_wall		ver_wall;

	double		ray_angle;
	int			cur_ray;
	double		beta;

	int			sprite_count;
	t_table		*angl_table;

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

typedef struct s_data
{
	t_mlx				mlx_data;

	int					game_state;
	t_point				mouse_click;
	t_point				main_button;
	t_point				pause_button;

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

	Music				music[MAX_MUSIC];
	char				*music_path[MAX_MUSIC];
	Sound				sound[MAX_SOUND];
	char				*sound_path[MAX_SOUND];

	t_table				angle_table[ANGLE_PRES * 360];
}						t_data;

//-------------------------------RAYCASTING------------------------------------
// thread.c
void	*thread_sprite(void *arg);
void	*thread_raycast(void *arg);
void	init_threads(t_raycast *raycast, void *(routine)(void *arg));

// helper.c
void		calc_norm_dist(t_raycast *raycast);
void		select_tex(t_raycast *raycast, t_wall *wall, int axis_flag);
void		init_common_info(t_data *data, t_char *player, t_raycast *raycast);
t_raycast	*init_raycast(t_data *data, t_char *player, t_raycast *raycast);
void		fill_ray_info(t_raycast *raycast);

// door.c
void		update_doors(t_door *doors);
t_door		*find_door(t_door *doors, int unit_x, int unit_y);
t_door		*create_door(t_door **doors_list, int grid_x, int grid_y);

// face_enemy.c
void	check_screen_center(t_raycast *raycast, t_sprite *sprite, t_point center);
void	check_statue_look(t_raycast *raycast, t_sprite *sprite);
void	chck_facing_enemy(t_raycast *raycast, t_sprite **sprite_array,
		t_char *player);

// sprite.c
void		sort_sprite_dist(t_raycast *raycast, t_sprite **sprite_array);
double		calc_angl_dif(t_raycast *raycast, t_sprite *srpite);
void		calc_sprite(t_raycast *raycast, t_sprite **sprites);
void		draw_sprite_pix(t_raycast *raycast, t_sprite *sprite, int x, int y);
void		draw_sprite(t_raycast *raycast, t_sprite *sprite);

// sprite_init.c
void		fill_sprite_info(t_sprite *new_sprite, t_data *data, int type);
t_sprite	*create_sprite(t_data *data, int type, int grid_x, int grid_y);
t_sprite	**init_spite_array(t_raycast *raycast);

// draw_utils.c
void	adjust_image_alpha(mlx_image_t *img, int new_alpha);
void		add_shadow(uint32_t *color, int dist);
void		fill_wall_info(t_raycast *raycast, t_wall *wall);
void	fill_floor_info(t_raycast *raycast, t_point *ceil_pos, int *dist, int y);
void	fill_ceil_info(t_raycast *raycast, t_point *ceil_pos, int *dist, int y);

// draw.c
void		draw_wall(t_raycast *raycast, int *y, t_wall *wall);
void		render_col(t_raycast *raycast, t_wall *wall);

// render.c
void	update_statue(t_data *data, t_char *player, t_sprite *sprites);
void	render(void *data_arg);
void	manage_menu(t_data *data, mlx_image_t **tex_img);
int		check_mouse_click(t_data *data, t_point *but);

// raycast.c
void		compre_dist(t_raycast *raycast, t_wall *hor_wall,
				t_wall *ver_wall);
void		cast_ray(t_raycast *raycast);
void		handle_sprites(t_raycast *raycast);
void		raycast(t_data *data);

// minimap_player.c
int			edge_function(t_point a, t_point b, t_point c);
bool		point_in_triangle(t_point p, t_point a, t_point b, t_point c);
void		norm_base(t_point *base_left, t_point *base_right, t_point *max, t_point *min);
void	fill_icon_with_color(mlx_image_t *minimap,
							t_point *tip, t_point *base_left, t_point *base_right);
void	draw_player(t_data *data, int view_angle_i, mlx_image_t *minimap, t_point *mid);

// minimap_utils.c
void	init_d_step(t_point *p1, t_point *p2, t_point *d, t_point *step);
void	draw_line(mlx_image_t *img, t_point *p1, t_point *p2, int color);

// minimap.c
void	draw_background(mlx_image_t *minimap);
void	draw_obj(t_data *data, t_point *mid_img, mlx_image_t *minimap);
void	draw_minimap(t_data *data, mlx_image_t *minimap);


// find_wall_utils.c
bool		is_on_map(t_data *data, t_point *p);
bool		extend_door(t_raycast *raycast, t_wall *wall, int axis);
bool		check_hit(t_raycast *raycast, t_wall *wall, int axis_flag);

// find_wall.c
void		init_wall(t_raycast *raycast, t_dpoint *temp,
				t_point *char_pos, int axis_flag);
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
void		clean_audio(t_data *data);
void		init_audio(t_data *data);

// clean.c
void		clean_map(t_data *data);
void		clean_mlx(t_data *data);
void		clean_all(t_data *data, char *perr_mess);

// init_mlx.c
bool		resize_image(mlx_image_t *img, int img_i);
void		*init_tex(t_mlx *mlx_data, mlx_texture_t **tex);
bool		put_images_to_window(t_data *data, t_mlx *mlx_data);
void		init_mlx(t_data *data);

// init.c
void		init_unit_map(t_data *data);
void		init_player(t_data *data);
void		init_angle_table(t_table *angle_table);
void		init_data(t_data *data);

// debug.c
void		show_fps(void);
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
