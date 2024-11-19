/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 21:09:34 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../ReFile/includes/all.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>

typedef enum e_draw
{
	DRAW_CELL,
	DRAW_WALL,
	DRAW_FLOOR,
}					t_draw;

typedef enum e_chunk_type
{
	CHUNK_WALL,
	CHUNK_EMPTY,
	CHUNK_VOID,
	CHUNK_PLAYER,
}					t_chunk_type;

typedef enum e_dir
{
	DIR_NORTH,
	DIR_SOUTH,
	DIR_EAST,
	DIR_WEAST,
}					t_dir;

typedef struct s_config
{
	t_file			*no;
	t_file			*so;
	t_file			*we;
	t_file			*ea;

	ssize_t			r_w;
	ssize_t			r_h;

	ssize_t			f_r;
	ssize_t			f_g;
	ssize_t			f_b;

	ssize_t			c_r;
	ssize_t			c_g;
	ssize_t			c_b;

	t_file			*map;
}					t_config;

typedef struct s_ray
{
	float			cur_dist;

	float			wall_height;
	float			start;
	float			end;
	float			end_x;
	float			end_y;

	float			cur_angle;
	float			angle_incr;

	int				w_line;
	t_dir			direction;
}					t_ray;

typedef struct s_chunk
{
	t_chunk_type	type;
}					t_chunk;

typedef struct s_map
{
	t_chunk			**chunks;
	char			*origin;
	ssize_t			l;
	ssize_t			h;
}					t_map;

typedef enum s_key
{
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_PLUS,
	KEY_MINUS,
	KEY_ARROW_LEFT,
	KEY_ARROW_RIGHT,
	KEY_VIEW_SWITCH,
	KEY_DEBUG_SWITCH,
}					t_key;

typedef struct s_win
{
	bool			map_view;
	bool			debug_view;

	bool			*keys;
	void			*mlx_ptr;
	void			*win_ptr;

	ssize_t			chunk_size;
	int				offset_x;
	int				offset_y;
}					t_win;

typedef struct s_player
{
	float			x;
	float			y;
	float			angle;
	float			angle_incr;
	float			fov;
}					t_player;

typedef struct s_data
{
	t_config		*config;
	t_map			*map;
	t_win			*win;
	t_player		*player;
}					t_data;

//! config
bool				texture_init(t_data *data);
bool				rgb_init(char *str, ssize_t *r, ssize_t *g, ssize_t *b);
bool				config_init(t_data *data, char *filepath);
bool				res_init(char *str, ssize_t *w, ssize_t *h);
bool				data_init(t_data *data, char *filepath);

//! map
bool				map_init(t_data *data);
t_chunk				**chunks_malloc(ssize_t l, ssize_t h);
bool				map_maker(t_map *map, char **raw_map);

//! utils
ssize_t				ft_atoi(const char *str);
char				*path_format(char *str);
bool				is_map_char(char *map_chars, char c);
char				*ft_itoa(int nb);

//! free
void				t_free(void *ptr);
void				t_rfree(char **ptr);
void				data_destructor(t_data *data);
void				config_destructor(t_data *data);
void				win_destructor(t_win *win);

//! print
void				print_checkpoint(char *checkpoint_name, bool succeed,
						bool lignfeed);
void				print_config(t_config *config);
void				print_chunks(t_map *map);

//! full fill
void				full_fill(t_map **map, ssize_t h, ssize_t l);
bool				fill_check(t_data *data);

//! game
int					game(t_data *data);
int					key_press(int keycode, t_data *data);
int					key_release(int keycode, t_data *data);
int					print_key(t_win *win);
void				update_player(t_data *data);

//! img
void				img_refresh(t_data *data);
void				my_mlx_pixel_put(t_img *img, int x, int y, int color);
void				img_put_stat(t_data *data);
void				img_null_pixel(t_data *data, t_img *img);
void				img_draw_map(t_data *data, t_img *img);
t_img				*img_new(t_data *data);
void				img_destructor(t_win *win, t_img *img);

void				handle_raycasting(t_data *data, t_img *img);
void				img_put_num(t_data *data, ssize_t w, ssize_t h,
						ssize_t num);
void				draw_line(t_data *data, t_img *img, int x0, int y0, int x1,
						int y1, int color);
t_ray				*ray_new(t_player *player);
void				get_ray_dist(t_data *data, t_img *img, t_ray *rc);

void				vertical_draw(t_data *data, t_img *img, t_ray *r_c,
						t_draw type_code);
int					rgb_to_hex(int r, int g, int b);
t_ray				*ray_new(t_player *player);
void				drunk_mode(t_data *data);
t_file				*get_texture(t_data *data, t_dir dir);
bool				identify_starting_angle(t_data *data, char *map);

#endif