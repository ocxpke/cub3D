#ifndef STRUCTS_H
#define STRUCTS_H

#include "cub3d.h"

typedef enum e_texture_type
{
	COLOR_TEXTURE,
	IMAGE_TEXTURE
} t_texture_type;

typedef struct s_wall_textures
{
	mlx_texture_t *north_tex;
	mlx_texture_t *south_tex;
	mlx_texture_t *east_tex;
	mlx_texture_t *west_tex;
	t_texture_type tipo;
	uint32_t color;
} t_wall_textures;

typedef struct s_ceil_floor_text
{
	mlx_texture_t **all_textures;
	t_texture_type tipo;
	uint32_t color;
	uint8_t num_text;
} t_ceil_floor_text;

typedef struct s_keys
{
	bool left_arrow;
	bool right_arrow;
	bool w_key;
	bool s_key;
	bool a_key;
	bool d_key;
} t_keys;

typedef struct s_player
{
	float posX;
	float posY;
	float deltaX;
	float deltaY;
	float ang;
	int8_t look_ns;
	int8_t look_ew;
	t_keys key_control;
} t_player;

typedef struct s_game
{
	char **map;
	mlx_t *window;
	mlx_image_t *map_view;
	mlx_image_t *game_view;
	t_wall_textures *wall_text;
	t_ceil_floor_text *floor_tex;
	t_ceil_floor_text *ceiling_tex;
	int map_width;
	int map_height;
	uint32_t init_width;
	uint32_t init_height;
	uint32_t ceiling;
	uint32_t floor;
	uint16_t pixels_cols;
} t_game;

typedef struct s_all
{
	t_game *game_wrap;
	t_player *player_info;
} t_all;

typedef struct s_raycast
{
	float player_posX;
	float player_posY;
	float minor_distance;
	float vertical_distance;
	float horizontal_distance;
	float arcotangente;
	float ray_x;
	float ray_y;
	int ray_number;
	int distance_of_field;
	int col_gross;
} t_raycast;

#endif
