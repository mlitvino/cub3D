/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:53:29 by mlitvino          #+#    #+#             */
/*   Updated: 2025/06/16 18:06:20 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42_Int.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define WIN_W 800
# define WIN_H 600

# define FOV 60
# define BLOCK_SIZE 512

# define WALL '1'

# define VERTICAL 0
# define HORIZONT 1

# define DEG_TO_RAD(a) ((a)*M_PI / 180.0)

enum
{
	NORTH,
	EAST,
	WEST,
	SOUTH,
	MAX_TEX,
};

typedef struct s_data	t_data;

//------------------------------Graphic----------------------------------

typedef struct s_dpoint
{
	double				x;
	double				y;
	double				h;
}						t_dpoint;

typedef struct s_point
{
	int					x;
	int					y;
	int					height;
}						t_point;

typedef struct s_rgbt
{
	int					r;
	int					g;
	int					b;
	int					t;
	int					rgbt;
}						t_rgbt;

typedef struct s_project
{
	int					dist;
	t_point				center;
}						t_project;

typedef struct s_raycast
{
	t_data				*data;
	t_project			*plane;
	mlx_image_t			*scr_img;
	char				**unit_map;

	int					flor_rgbt;
	int					ceil_rgbt;

	int					view_angle;
	t_point				char_pos;

	t_point				hor_wall;
	t_point				ver_wall;
	int					hor_dist;
	int					ver_dist;

	mlx_image_t			*wall_img;
	int					tex_x;

	double				ray_angle;
	int					cur_ray;
	double				beta;

	int					tex_indx;
}						t_raycast;

//-------------------------------GAME------------------------------------

typedef struct s_keys
{
	int					w;
	int					a;
	int					s;
	int					d;
	int					left;
	int					right;
	int					esc;
}						t_keys;

typedef struct s_pov
{
	t_point				view_pos;
	int					view_angl;
	int					fov;

}						t_pov;

typedef struct s_char
{
	t_data				*data;

	t_pov				pov;
	int					height;

	int					hitbox_radius;
	t_point				pos;

	int					move_spd;
	int					turn_spd;
}						t_char;

//-------------------------------GENERAL------------------------------------

typedef struct s_mlx
{
	mlx_t				*mlx_ptr;

	mlx_image_t			*scr_img;

	char				**ceiling_colour;
	char				**floor_colour;
	char				*tex_path[MAX_TEX];
	mlx_texture_t		*textrs[MAX_TEX];
	mlx_image_t			*textrs_img[MAX_TEX];
}						t_mlx;

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

	t_char				player;
	t_keys				keys;

	t_project			plane;
	int					rays_count;
	double				rays_angle;
	t_rgbt				flor_rgb;
	t_rgbt				ceil_rgb;
}						t_data;

//-------------------------------RAYCASTING------------------------------------

// clean.c
void					clean_map(t_data *data);
void					clean_mlx(t_data *data);
void					clean_all(t_data *data, char *perr_mes);

// init.c
void					init_unit_map(t_data *data);
void					init_mlx(t_data *data);
void					init_data(t_data *data);

// helper.c
void					calc_norm_dist(t_raycast *raycast);
void					select_tex(t_raycast *raycast, int axis_flag);
t_raycast				init_raycast(t_data *data, t_char *player);
void					fill_ray_info(t_raycast *raycast);

// raycast.c
void					map_wall(t_raycast *raycast, int y, int wall_h,
							int wall_top);
void					render_col(t_raycast *raycast, t_point wall,
							int wall_dist, int tex_indx);
void					compre_dist(t_raycast *raycast, t_point hor_wall,
							t_point ver_wall);
void					cast_ray(t_raycast *raycast, double ray_angl);
void					raycast(t_data *data);

// find_wall.c
void					init_wall(t_point char_pos, t_dpoint *temp,
							double ray_angl, int axis_flag);
void					adjust_wall(t_dpoint *temp, double dx, double dy);
void					init_delta(int axis_flag, double *dx, double *dy,
							double ray_angl);
void					norm_fract(t_dpoint *temp, t_point *line, int axis_flag,
							double ray_angl);
bool					find_wall(t_raycast *raycast, t_point *wall,
							int axis_flag, int *dist);

// utils.c
bool					is_on_map(t_data *data, t_point *p);
double					deg_rad(double deg);
double					calc_dist(t_point p1, t_point p2);
uint32_t				extract_rgba(uint8_t *raw);

//-------------------------------MOVEMENT------------------------------------
void					key_event_handler(mlx_key_data_t keydata, void *param);
void					move_player(t_char *player, double angle_offset);
int						check_for_wall_collision(t_char *player, double new_x,
							double new_y);
void					rotate_player_right(t_char *player);
void					rotate_player_left(t_char *player);

//----------------------------------PARSING-------------------------------------

// free error functions
int						return_invalid_element(void);
int						error_exit(char *message);
char					**error_return(char *message);
int						free_return(int *data);
int						perror_free_map(char **map);
char					**free_map(char **map, int fd);
void					free_colours_textures_strings(t_data *data);
int						error_free_return(char *message, t_data *data);
int						free_map_return(t_data *data);
int						free_error_exit(char *line, char *colour);
char					**perror_return(void);
int						perror_return_int(int *data);
char					**perror_free(char **map_data, int fd);
int						perror_exit(char *line);
char					*perror_exit_null(void);

// utils
int						valid_end_of_string(int *i, int done, char *line,
							char *colour);
int						valid_colour_number(char *colour, int floor_ceiling,
							int rgb, t_data *data);
int						valid_colours(t_data *data);
char					*set_colour(char *line, int *i, int done);
int						set_rgb(int floor_or_ceiling, char *line_trim, int *i,
							t_data *data);
int						free_element_map(int *element, t_data *data);
int						create_temp_map(char **map, int *i, t_data *data);
int						is_identifier(char *line);
int						is_map_element(char *line, int *map_element,
							t_data *data);
int						is_empty_line(char *line);
void					init_null(t_data *data);
int						fill_map(t_data *data, char **map_data, int fd);
int						valid_extension(const char *filename);
char					**pad_map(char **map, int height, t_data *data);
int						set_floor_colour(t_data *data, char *line_trim, int *i);
int						set_ceiling_colour(t_data *data, char *line_trim,
							int *i);
int						set_floor_ceiling(t_data *data, char *element,
							char *line);
char					**read_file(char *filename, t_data *data);
int						valid_map(t_data *data);
int						is_valid_surrounding(char **map, t_data *data);
int						is_valid_data(char **map, t_data *data, int line_count);
int						check_map_borders(char **map, int height);
int						longest_line(char **map, int height);
int						fill_padded_map(int height, t_data *data,
							char **padded_map, char **map);
int						last_line_no_newline(char *line);
int						check_double_element_wall(int *map_element,
							char *element, char *line, t_data *data);

#endif
