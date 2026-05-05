/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:40:48 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/03 15:50:14 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

#include "cub3d.h"

typedef enum e_coll_tex
{
	WALL_TEX,
	DOOR_TEX
}						t_coll_tex;

typedef struct s_color
{
	uint8_t				red;
	uint8_t				green;
	uint8_t				blue;
	uint8_t				alpha;
}						t_color;

typedef struct s_checklist
{
	int					no_tex;
	int					so_tex;
	int					we_tex;
	int					ea_tex;
	int					fl_col;
	int					cl_col;
	int					ok;
}						t_checklist;

typedef struct s_tex_col
{
	char				*no_tex;
	char				*no_tex_path;
	char				*so_tex;
	char				*so_tex_path;
	char				*we_tex;
	char				*we_tex_path;
	char				*ea_tex;
	char				*ea_tex_path;
	char				*fl_col;
	t_color				*fl_col_val;
	char				*cl_col;
	t_color				*cl_col_val;
}						t_tex_col;

typedef struct s_map
{
	char				**map;
	int					rows;
	int					cols;
	int					pstart_x;
	int					pstart_y;
	char				pstart_orientation;
	int					key_count;
	int					door_count;
	t_tex_col			*tex_col_s;
}						t_map;

typedef struct s_dpar
{
	t_map				*map_s;
	t_checklist			*checklist_s;
	char				**file_cont;
	int					fd;
}						t_dpar;

typedef enum e_texture_type
{
	COLOR_TEXTURE,
	IMAGE_TEXTURE
}						t_texture_type;

typedef struct s_wall_textures
{
	mlx_texture_t		*north_tex;
	mlx_texture_t		*south_tex;
	mlx_texture_t		*east_tex;
	mlx_texture_t		*west_tex;
	mlx_texture_t		*door_tex;
	t_texture_type		type;
	uint32_t			color;
}						t_wall_textures;

typedef struct s_ceil_floor_tex
{
	mlx_texture_t		**all_textures;
	t_texture_type		type;
	uint32_t			color;
	uint8_t				num_texs;
}						t_ceil_floor_tex;

typedef struct s_keys
{
	bool				left_arrow;
	bool				right_arrow;
	bool				w_key;
	bool				s_key;
	bool				a_key;
	bool				d_key;
}						t_keys;

typedef struct s_player
{
	float				posx;
	float				posy;
	float				deltax;
	float				deltay;
	float				ang;
	t_keys				key_control;
}						t_player;

typedef struct s_game
{
	char				**map;
	mlx_t				*window;
	mlx_image_t			*map_view;
	mlx_image_t			*game_view;
	t_wall_textures		wall_text;
	t_ceil_floor_tex	floor_tex;
	t_ceil_floor_tex	ceiling_tex;
	int					map_width;
	int					map_height;
	uint32_t			init_width;
	uint32_t			init_height;
	int32_t				tile_size;
	int32_t				offset_x;
	int32_t				offset_y;
	int32_t				player_size;
	uint16_t			pixels_cols;
	uint16_t			col_gross;
}						t_game;

typedef struct s_all_struct
{
	t_dpar				*parser_data;
	t_game				*game_wrap;
	t_player			*player_info;
}						t_all_structs;

typedef struct s_raycast_ceil_fl
{
	float				cos_corrected;
	float				cos_ray;
	float				sin_ray;
	float				ceil_fl_dy;
	float				ceil_fl_ang;
	float				ceil_fl_straight_dist;
	float				ceil_fl_true_dist;
	float				ceil_fl_world_x;
	float				ceil_fl_world_y;
	uint16_t			ceil_fl_tex_x;
	uint16_t			ceil_fl_tex_y;
}						t_raycast_ceil_fl;

typedef struct s_raycast_ceil_fl
{
	float cos_corrected;
	float cos_ray;
	float sin_ray;
	float ceil_fl_dy;
	float ceil_fl_ang;
	float ceil_fl_straight_dist;
	float ceil_fl_true_dist;
	float ceil_fl_world_x;
	float ceil_fl_world_y;
	uint16_t ceil_fl_tex_x;
	uint16_t ceil_fl_tex_y;
} t_raycast_ceil_fl;

typedef struct s_raycast
{
	t_raycast_ceil_fl	ceil_fl_vars;
	float				player_angle;
	float				player_posx_cube;
	float				player_posy_cube;
	float				player_posx_map;
	float				player_posy_map;
	float				minor_distance;
	float				arc_tan;
	float				neg_tan;
	float				ray_x;
	float				ray_y;
	float				ray_angle;
	float				ray_x_offset;
	float				ray_y_offset;
	float				horizontal_dist;
	float				horizontal_x;
	float				horizontal_y;
	float				vertical_dist;
	float				vertical_x;
	float				vertical_y;
	float				texture_x_hp;
	float				texture_y_hp;
	float				save_tex_y;
	float				texture_steps;
	float				corrected_angle;
	float				wall_len;
	float				wall_start;
	int					ray_number;
	int					distance_of_field;
	int					map_x;
	int					map_y;
	int					iter_gross;
	uint16_t			ray_ct;
	int8_t				hor_ver;
	int8_t				ns_ew;
	uint8_t				ceil_frame;
	uint8_t				floor_frame;
	t_coll_tex			coll_tex_ver;
	t_coll_tex			coll_tex_hor;
	t_coll_tex			coll_tex;
}						t_raycast;

#endif
