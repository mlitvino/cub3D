/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablodorn <ablodorn@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:53:29 by mlitvino          #+#    #+#             */
/*   Updated: 2025/07/01 13:43:05 by ablodorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "raudio.h"
# include "MLX42/MLX42_Int.h"
# include "float.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

# define WIN_W 1280
# define WIN_H 720

# define MINIMAP_W (WIN_W / 5)
# define MINIMAP_H (WIN_W / 6)

# define SKY_W 1440
# define SKY_H 5000

# define HUD_W (WIN_W / 4)
# define HUD_H (WIN_H / 10)

# define MAIN_BUTTON                  \
	(t_dpoint)                       \
	{                                \
		1920.0 / 79, 1080.0 / 603, 0 \
	}
# define PAUSE_BUTTON                  \
	(t_dpoint)                        \
	{                                 \
		1920.0 / 764, 1080.0 / 583, 0 \
	}
# define BUTTON_DX (1920.0 / 369)
# define BUTTON_DY (1080.0 / 108)
# define BUTTON_DY2 (1080.0 / 52)

# define MAX_THRD 6

# define FOV 60
# define BLOCK_SIZE 512
# define ANGLE_PRES 100

# define MINIMAP_ZOOM 30
# define ICON_SIZE 14
# define ICON_BASE 5

# define MODIF_BRIGHT 0.5

# define STATUE_MAX_VIS 4
# define W_STATUE_VIS_DEC 25
# define H_STATUE_VIS_DEC 3

# define PLAYER_HP 6
# define PLAYER_AMMO 8
# define ENEMY_HP 2

# define START 100
# define EXIT_STATE 101

# define VALID_CHARS "0XFf12345RDMNSWECBGTAdswb "
# define WALLS "12345"
# define DOORS "DMs"
# define SPRITES "BCGdAwTb"
# define FLOORS "0XRFf"

# define EMPTY '0'
# define BLOOD_GRASS 'X'
# define ROAD 'R'
# define FLOOR 'F'
# define STONE_FLOOR 'f'

# define WALL '1'
# define ROCK_WALL '2'
# define WAGON '3'
# define WOOD_WALL '4'
# define STONE_WALL '5'

# define TREE 'T'
# define DEAD_MAN 'd'
# define STATUE 'C'
# define WOLF 'B'
# define BONES 'b'
# define WOODPILE 'w'

# define DOOR 'D'
# define MET_DOOR 'M'
# define STONE_DOOR 's'

# define EXIT 'G'
# define AMMO 'A'

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
	ROCK_TEX,
	WAGON_TEX,
	WOOD_WALL_TEX,
	WALL_TEX,
	STONE_WALL_TEX,
	DOOR_TEX,
	MET_DOOR_TEX,
	STONE_DOOR_TEX,
	FLOOR_TEX,
	STONE_FLOOR_TEX,
	GROUND_TEX,
	BLD_GRASS_TEX,
	ROAD_TEX,
	CEILING_TEX,
	SKY_TEX,
	BONES_TEX,
	WOODPILE_TEX,
	WOLF_STAY,
	WOLF_WALK1,
	WOLF_WALK2,
	WOLF_ATTCK,
	WOLF_DEAD,
	STATUE_GREY,
	STATUE_RED,
	EVIL_TREE,
	DEAD_MAN_TEX,
	AMMO_TEX,
	EXIT_TEX,
	HUD_TEX,
	N0_TEX,
	N1_TEX,
	N2_TEX,
	N3_TEX,
	N4_TEX,
	N5_TEX,
	N6_TEX,
	N7_TEX,
	N8_TEX,
	N9_TEX,
	MAIN_MENU,
	PAUSE,
	DEATH,
	CONTROLS,
	WIN,
	STATUE_FACE,
	CROSSBOW1,
	CROSSBOW2,
	MAX_TEX
}							t_texture;

# define NORTH_PATH "textures/wall/forest.png"
# define EAST_PATH "textures/wall/forest.png"
# define WEST_PATH "textures/wall/forest.png"
# define SOUTH_PATH "textures/wall/forest.png"
# define ROCK_TEX_PATH "textures/wall/rock_wall.png"
# define WAGON_TEX_PATH "textures/wall/wagon.png"
# define WALL_TEX_PATH "textures/wall/forest.png"
# define WOOD_WALL_PATH "textures/wall/wood_wall.png"
# define STONE_WALL_PATH "textures/wall/stone_wall.png"

# define MET_DOOR_TEX_PATH "textures/metal_door.png"
# define DOOR_TEX_PATH "textures/wood_door.png"
# define STONE_DOOR_PATH "textures/stone_door.png"

# define STONE_FLOOR_PATH "textures/floor/stone_floor.png"
# define FLOOR_TEX_PATH "textures/floor/wood_floor.png"
# define BLD_GRASS_PATH "textures/floor/blood_grass.png"
# define ROAD_PATH "textures/floor/stone_road.png"
# define GROUND_TEX_PATH "textures/floor/grass.png"
# define CEILING_TEX_PATH "textures/ceiling/wood_ceiling.png"
# define SKY_TEX_PATH "textures/ceiling/sky.png"

# define BONES_PATH "textures/decor/bones.png"
# define WOODPILE_PATH "textures/decor/woodpile.png"
# define DEAD_MAN_PATH "textures/decor/dead_man.png"
# define WOLF_STAY_PATH "textures/wolf/wolf_stay.png"
# define WOLF_WALK1_PATH "textures/wolf/wolf_walk1.png"
# define WOLF_WALK2_PATH "textures/wolf/wolf_walk2.png"
# define WOLF_ATTCK_PATH "textures/wolf/wolf_attck.png"
# define WOLF_DEAD_PATH "textures/wolf/wolf_dead.png"
# define STATUE_GREY_PATH "textures/statue/statue_grey.png"
# define STATUE_RED_PATH "textures/statue/statue_red.png"
# define EVIL_TREE_PATH "textures/decor/evil_tree.png"
# define EXIT_TEX_PATH "textures/exit.png"
# define AMMO_TEX_PATH "textures/decor/ammo.png"

# define HUD_PATH "textures/hud/hp_ammo.png"

# define N0_PATH "textures/hud/n0.png"
# define N1_PATH "textures/hud/n1.png"
# define N2_PATH "textures/hud/n2.png"
# define N3_PATH "textures/hud/n3.png"
# define N4_PATH "textures/hud/n4.png"
# define N5_PATH "textures/hud/n5.png"
# define N6_PATH "textures/hud/n6.png"
# define N7_PATH "textures/hud/n7.png"
# define N8_PATH "textures/hud/n8.png"
# define N9_PATH "textures/hud/n9.png"

# define MAIN_MENU_PATH "textures/menu/main_menu.png"
# define PAUSE_PATH "textures/menu/pause.png"
# define DEATH_PATH "textures/menu/death.png"
# define CONTROLS_PATH "textures/menu/controls.png"
# define WIN_PATH "textures/menu/win.png"

# define STATUE_FACE_PATH "textures/statue/statue_face.png"
# define CROSSBOW1_PATH "textures/crossbow1.png"
# define CROSSBOW2_PATH "textures/crossbow2.png"

# define S_STONE_DOOR_PATH "audio/stone_door.mp3"
# define S_DOOR_PATH "audio/wood_door.mp3"
# define S_MET_DOOR_PATH "audio/metal_door.mp3"
# define S_SHOT_PATH "audio/shot.mp3"
# define S_WOLF_CHASE_PATH "audio/wolf_chase.mp3"
# define S_WOLF_GROWL_PATH "audio/wolf_growl.mp3"
# define S_STATUE_HUM_PATH "audio/hum.mp3"
# define S_VICTORY_PATH "audio/victory.mp3"
# define S_PLAYER_DYING_PATH "audio/player_dying.mp3"

# define M_CASTLE_PATH "audio/castle.mp3"
# define M_STORM_PATH "audio/storm.mp3"
# define M_FOREST_PATH "audio/forest.mp3"
# define M_PLAYER_STEP_PATH "audio/player_step.mp3"
# define M_WOLF_STEP_PATH "audio/wolf_step.mp3"

# define GREEN_COL 0x124200ff
# define ORANGE_COL 0xcc8b00ff
# define GRAY_COL 0x545454ff
# define BROWN_COL 0x6b3e00ff

typedef enum e_music
{
	M_PLAYER_STEP,
	M_WOLF_STEP,
	M_FOREST,
	M_STORM,
	M_CASTLE,
	MAX_MUSIC
}							t_music;

typedef enum e_sound
{
	S_VICTORY,
	S_PLAYER_DYING,
	S_SHOT,
	S_MET_DOOR,
	S_STONE_DOOR,
	S_DOOR,
	S_WOLF_CHASE,
	S_WOLF_GROWL,
	S_STATUE_HUM,
	MAX_SOUND
}							t_sound;

typedef struct s_data		t_data;
typedef struct s_raycast	t_raycast;
typedef struct s_char		t_char;

//------------------------------Graphic----------------------------------

typedef struct s_dpoint
{
	double					x;
	double					y;
	double					h;

}							t_dpoint;

typedef struct s_point
{
	int						x;
	int						y;
	int						h;

}							t_point;

typedef struct s_path
{
	t_point					pos;
	struct s_path			*parent;
}							t_path;

typedef struct s_rgbt
{
	int						r;
	int						g;
	int						b;
	int						t;
	uint32_t				rgbt;

}							t_rgbt;

typedef struct s_project
{
	int						width;
	int						height;
	int						dist;
	t_point					center;

}							t_project;

typedef struct s_wall
{
	t_point					pos;
	int						dist;
	int						type;
	int						door_len;

	int						h;
	int						top;
	t_point					tex_pos;

	int						img_i;
	mlx_image_t				*img;

}							t_wall;

typedef struct s_door
{
	int						state;
	int						len;
	int						grid_x;
	int						grid_y;
	int						move_spd;
	int						type;

	struct timeval			time_opened;

	struct s_door			*next;

}							t_door;

typedef struct s_sprite
{
	mlx_image_t				*cur_img;
	int						state;
	mlx_image_t				**tex_imgs;

	int						hp;
	int						hitbox_radius;
	t_point					pos;

	double					dist_player;
	int				move_rate;
	int				move_spd;
	int				turn_spd;
	int			attack_range;
	int			attack_rate;
	int				has_player_in_sight;
	t_dpoint			last_seen;
	int				moved;

	bool					visible;
	t_path					*path;
	int						walkable;
	int						type;
	int						dist;

	t_point					size;
	t_point					tex_p;

	int						height;
	int						width;
	int						top;
	int						left;
	double					angle;

	struct s_sprite			*next;

}							t_sprite;

//-------------------------------GAME------------------------------------
typedef struct s_delta
{
	int						dx[4];
	int						dy[4];
}							t_delta;

typedef struct s_bfs
{
	t_path					*queue[150];
	int						**visited;
	int						front;
	int						rear;
}							t_bfs;

typedef struct s_keys
{
	int						w;
	int						a;
	int						s;
	int						d;
	int						left;
	int						right;
	int						up;
	int						down;
	int						e;
	int						esc;
	int						tab;

	int						click;
	t_point					click_pos;
	int						cursor;
}							t_keys;

typedef struct s_pov
{
	t_point					view_pos;
	double					view_angl;
	int						fov;

}							t_pov;

typedef struct s_char
{
	t_data					*data;

	int						hp;
	int						ammo;
	int						door_facing;
	t_pov					pov;
	double					height;

	int						hitbox_radius;
	t_sprite				*facing_enemy;
	t_sprite				*facing_statue;
	t_dpoint				pos;

	int						move_spd;
	int						turn_spd;

	bool					is_shooting;
	int						is_moving;
	int						mov_height;
	double					bobbing_time;

	double					wall_rt;
	double					ceiling_rt;
	double					floor_rt;
}							t_char;

typedef struct s_table
{
	float					sin;
	float					cos;
	float					tan;
	float					beta;
}							t_table;

typedef struct s_raycast
{
	t_data					*data;
	t_project				*plane;
	mlx_image_t				*scr_img;
	char					**unit_map;
	t_door					*door_list;

	int						thread_chunk;
	t_sprite				*thread_sprite;
	pthread_t				threads[MAX_THRD];
	int						thrd_i;

	int						flor_rgbt;
	int						ceil_rgbt;

	t_char					*player;

	double					view_angle;
	t_point					char_pos;

	double					dx;
	double					dy;
	int						axis;

	t_wall					hor_wall;
	t_wall					ver_wall;

	double					ray_angle;
	int						cur_ray;
	double					beta;

	int						sprite_count;
	t_table					*angl_table;

}							t_raycast;

//-------------------------------GENERAL------------------------------------

typedef struct s_mlx
{
	mlx_t					*mlx_ptr;

	mlx_image_t				*scr_img;
	t_point					scr_size;
	mlx_image_t				*minimap;

	char					**ceiling_colour;
	char					**floor_colour;
	char					*tex_path[MAX_TEX];
	mlx_texture_t			*textrs[MAX_TEX];
	mlx_image_t				*textrs_img[MAX_TEX];

}							t_mlx;

typedef struct s_data
{
	t_mlx					mlx_data;
	int						game_state;
	int						fps;

	char					**grid_map;
	char					**unit_map;
	char					**map_data;
	char					**work_map;
	int						line_count;
	int						map_h;
	int						map_w;

	t_door					*door_list;
	t_sprite				*sprite_list;

	t_char					player;
	t_keys					keys;

	t_project				plane;
	int						rays_count;
	int						rays_dist[WIN_W];
	double					rays_angle;
	t_rgbt					flor_rgb;
	t_rgbt					ceil_rgb;

	Music					*main_music;
	Music					music[MAX_MUSIC];
	Sound					sound[MAX_SOUND];

	t_table					angle_table[ANGLE_PRES * 360];
}							t_data;

//-------------------------------RAYCASTING------------------------------------
// thread.c
void						*thread_sprite(void *arg);
void						*thread_raycast(void *arg);
void						init_threads(t_raycast *raycast,
								void *(routine)(void *arg));

// helper.c
void						calc_norm_dist(t_raycast *raycast);
void						select_tex(t_raycast *raycast, t_wall *wall,
								int axis_flag);
void						init_common_info(t_data *data, t_char *player,
								t_raycast *raycast);
t_raycast					*init_raycast(t_data *data, t_char *player,
								t_raycast *raycast);
void						fill_ray_info(t_raycast *raycast);

// door.c
void						update_doors(t_door *doors, t_data *data);
t_door						*find_door(t_door *doors, int unit_x, int unit_y);
t_door						*create_door(t_data *data, t_door **doors_list,
								int grid_x, int grid_y);

// face_enemy.c
void						check_screen_center(t_raycast *raycast,
								t_sprite *sprite, t_point center);
void						check_statue_look(t_raycast *raycast,
								t_sprite *sprite);
void						chck_facing_enemy(t_raycast *raycast,
								t_sprite **sprite_array, t_char *player);

// sprite.c
void						sort_sprite_dist(t_raycast *raycast,
								t_sprite **sprite_array);
double						calc_angl_dif(t_raycast *raycast, t_sprite *srpite);
void						calc_sprite(t_raycast *raycast, t_sprite **sprites);
void						draw_sprite_pix(t_raycast *raycast,
								t_sprite *sprite, int x, int y);
void						draw_sprite(t_raycast *raycast, t_sprite *sprite);

// sprite_init.c
void						set_sprite_tex(t_sprite *new_sprite, t_data *data,
								int type);
void						fill_sprite_info(t_sprite *new_sprite, t_data *data,
								int type);
t_sprite					*create_sprite(t_data *data, int type, int grid_x,
								int grid_y);
t_sprite					**init_spite_array(t_raycast *raycast);

// draw_utils.c
void						adjust_image_alpha(mlx_image_t *img, int new_alpha);
void						add_shadow(uint32_t *color, int dist);
void						fill_wall_info(t_raycast *raycast, t_wall *wall);
mlx_image_t					*fill_floor_info(t_raycast *raycast,
								t_point *ceil_pos, int *dist, int y);
mlx_image_t					*fill_ceil_info(t_raycast *raycast,
								t_point *ceil_pos, int *dist, int y);

// draw.c
void						draw_wall(t_raycast *raycast, int *y, t_wall *wall);
void						render_col(t_raycast *raycast, t_wall *wall);

// raycast.c
void						compre_dist(t_raycast *raycast, t_wall *hor_wall,
								t_wall *ver_wall);
void						cast_ray(t_raycast *raycast);
void						handle_sprites(t_raycast *raycast);
void						raycast(t_data *data);

// find_wall_utils.c
bool						is_on_map(t_data *data, t_point *p);
bool						extend_door(t_raycast *raycast, t_wall *wall,
								int axis);
bool						check_hit(t_raycast *raycast, t_wall *wall,
								int axis_flag);

// find_wall.c
void						init_wall(t_raycast *raycast, t_dpoint *temp,
								t_point *char_pos, int axis_flag);
void						adjust_wall(t_raycast *raycast, t_dpoint *temp);
void						init_delta(t_raycast *raycast, int axis_flag);
void						norm_fract(t_dpoint *temp, t_wall *wall,
								int axis_flag, double ray_angl);
bool						find_wall(t_raycast *raycast, t_wall *wall,
								int axis_flag);

// raycast_utils.c
double						deg_rad(double deg);
long double					calc_dist(t_point p1, t_point p2);
uint32_t					extract_rgba(uint8_t *raw);

//-------------------------------MOVEMENT------------------------------------
void						resize_handler(int32_t width, int32_t height,
								void *data_arg);
void						mouse_hook(mouse_key_t button, action_t action,
								modifier_key_t mods, void *param);
void						key_event_handler(mlx_key_data_t keydata,
								void *param);
void						move_player(t_char *player, double angle_offset);
int							check_for_wall_collision(t_char *player,
								double new_x, double new_y);
void						rotate_player_right(t_char *player);
void						rotate_player_left(t_char *player);

//-------------------------------GENERAL------------------------------------

// minimap_player.c
int							edge_function(t_point a, t_point b, t_point c);
bool						point_in_triangle(t_point p, t_point a, t_point b,
								t_point c);
void						norm_base(t_point *base_left, t_point *base_right,
								t_point *max, t_point *min);
void						fill_icon_with_color(mlx_image_t *minimap,
								t_point *tip, t_point *base_left,
								t_point *base_right);
void						draw_player(t_data *data, int view_angle_i,
								mlx_image_t *minimap, t_point *mid);

// minimap_utils.c
void						init_d_step(t_point *p1, t_point *p2, t_point *d,
								t_point *step);
void						draw_line(mlx_image_t *img, t_point *p1,
								t_point *p2, int color);

// minimap.c
void						put_minimap_pix(t_data *data, t_point map_pos,
								int x, int y);
void						draw_background(mlx_image_t *minimap);
void						draw_obj(t_data *data, t_point *mid_img,
								mlx_image_t *minimap);
void						draw_minimap(t_data *data, mlx_image_t *minimap);

// update_player.c
void						update_player_ratio(t_char *player);
long						get_time_in_ms(void);
void						update_bobbing(t_char *player);
void						update_player(t_data *data, t_char *player);

// updte_sprite.c
void						update_statue_alpha(t_data *data, t_char *player);
void						update_statue(t_data *data, t_char *player,
								t_sprite *statue);
void						update_sprites(t_data *data, t_sprite *sprites);

// render.c
void						draw_aim_cross(mlx_image_t *scr_img);
void						show_fps(t_data *data);
void						update_audio(t_data *data);
void						update_hud(t_char *player, mlx_image_t **tex_img);
void						render(void *data_arg);

// menu.c
void						change_game_state(t_data *data, int new_state);
void						init_buttons(t_dpoint *but_r, t_point *d, int *dy2,
								t_point scr_size);
int							check_mouse_click(t_data *data, t_dpoint but_r,
								t_point scr_size);
void						manage_menu(t_data *data, mlx_image_t **tex_img);

// action.c
void						get_damage(t_data *data, t_sprite *spr,
								t_char *player);
void						shoot(t_data *data, t_char *player);

// audio.c
void						tune_audio(t_data *data);
void						clean_audio(t_data *data);
void						init_audio(t_data *data);

// clean.c
void						clean_map(t_data *data);
void						clean_mlx(t_data *data);
void						clean_obj(t_data *data);
void						clean_all(t_data *data, char *perr_mess);

// init_utils.c
bool						resize_image(mlx_image_t *img, int img_i);
void						replace_unit_points(t_data *data, int grid_x,
								int grid_y);

// init_mlx.c
void						*init_tex(t_mlx *mlx_data, mlx_texture_t **tex);
void						init_hud(t_data *data, t_mlx *mlx_data, mlx_t *mlx);
void						put_img_to_win(t_data *data, mlx_image_t *img,
								int img_i);
bool						put_images_to_window(t_data *data, t_mlx *mlx_data);
void						init_mlx(t_data *data);

// init.c
void						init_obj(t_data *data);
void						init_unit_map(t_data *data);
void						init_player(t_data *data);
void						init_angle_table(t_table *angle_table);
void						init_data(t_data *data);

// debug.c
void						draw_menu_but_grid(t_data *data, int main);
void						show_sprites(t_sprite **sprite_array,
								t_sprite *sprite_list);
void						show_doors(t_door *list);
void						show_char_pos(t_data *data, t_char *chr);
void						show_unit_map(t_data *data);
void						show_redline(t_data *data);
void						draw_aim_cross(mlx_image_t *scr_img);

//----------------------------------PARSING------------------------------------

// free error functions
int							return_invalid_element(void);
int							error_exit(char *message);
char						**error_return(char *message);
int							free_return(int *data);
int							perror_free_map(char **map);
char						**free_map(char **map, int fd);
int							error_free_return(char *message, t_data *data);
int							free_map_return(t_data *data);
int							free_error_exit(char *line, char *colour);
char						**perror_return(void);
int							perror_return_int(int *data);
char						**perror_free(char **map_data, int fd);
int							perror_exit(char *line);
char						*perror_exit_null(void);

// utils
int							valid_end_of_string(int *i, int done, char *line,
								char *colour);
int							valid_colour_number(char *colour, int floor_ceiling,
								int rgb, t_data *data);
int							valid_colours(t_data *data);
char						*set_colour(char *line, int *i, int done);
int							set_rgb(int floor_or_ceiling, char *line_trim,
								int *i, t_data *data);
int							free_element_map(int *element, t_data *data);
int							create_temp_map(char **map, int *i, t_data *data);
int							is_identifier(char *line);
int							is_map_element(char *line, int *map_element,
								t_data *data);
int							is_empty_line(char *line);
void						init_null(t_data *data);
int							fill_map(t_data *data, char **map_data, int fd);
int							valid_extension(const char *filename);
char						**pad_map(char **map, int height, t_data *data);
void						set_angle(char angle, t_data *data);

int							set_floor_colour(t_data *data, char *line_trim,
								int *i);
int							set_ceiling_colour(t_data *data, char *line_trim,
								int *i);
int							set_floor_ceiling(t_data *data, char *element,
								char *line);
char						**read_file(char *filename, t_data *data);
int							valid_map(t_data *data);
int							is_valid_surrounding(t_data *data);
int							is_valid_data(char **map, t_data *data,
								int line_count);
int							check_map_borders(char **map, int height);
int							longest_line(char **map, int height);
int							fill_padded_map(int height, t_data *data,
								char **padded_map, char **map);
int							last_line_no_newline(char *line);
int							check_double_element_wall(int *map_element,
								char *element, char *line, t_data *data);
int							check_doors(char **map);

void						handle_mouse_rotation(t_data *game);
void						open_close_door(t_data *data);

void						update_wolf(t_data *data);
t_path						*bfs_find_path(t_data *data, t_point start,
								t_dpoint goal);
int							init_visited(int ***visited, t_data *data);
void						init_delta_path(t_delta *d);
t_path						*create_node(int x, int y, t_path *parent);
void						free_queue_except_path(t_path **queue,
								int rear, t_path *path_end);
int							has_line_of_sight(t_sprite *enemy, t_char *player,
								char **map);
t_path						*reverse_path(t_path *end);
void						free_path(t_path *path);
void						move_to_goal(t_sprite *sprite, t_data *data);
int							can_move_wall_enemy(t_sprite *sprite, float new_x,
								float new_y, t_data *data);
int							can_move_enemy_collision(t_sprite *sprite,
								float new_x, float new_y, t_data *data);
void						free_visited(int **visited, int height);
int							is_valid_tile(char **map, t_data *data, int x,
								int y);
void						no_path(t_sprite *sprite);
void	check_end_of_path(t_sprite *sprite);

void	free_paths(t_sprite *sprites);
void	set_new_pos(t_data *data, t_sprite *sprite,
	float new_x, float new_y);
void	switch_img(t_sprite *sprite);
int	no_path_return(t_sprite *sprite);
void	wolf_action(t_sprite *sprite, t_data *data);
int player_inside_door(t_data *data, t_door *door);
int enemy_inside_door(t_data *data, t_door *door);
int	has_10_seconds_passed(struct timeval start);
struct timeval	get_current_time(void);
int	*check_for_door(char **map, int player_x, int player_y,
		t_data *data);
int	can_move_wall(t_char *player, double new_x, double new_y);
int	can_move_door(t_char *player, double new_x, double new_y);

#endif
