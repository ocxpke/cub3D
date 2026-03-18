#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

/**
 * @brief Describes player's state
 *
 * @param posX Describes the actual X axis position
 * @param posY Describes the actual Y axis position
 * @param dirX Describes where the player is looking at on the X axis
 * @param dirY Describes where the player is looking at on the Y axis
 *
 */

typedef struct s_keys
{
	bool left_arrow;
	bool right_arrow;
	bool w_key;
	bool s_key;
	bool a_key;
	bool d_key;
}	t_keys;

typedef struct s_player
{
	int8_t look_ns;
	int8_t look_ew;
	float posX;
	float posY;
	float dirX;
	float dirY;
	float ang;
	t_keys key_control;
} t_player;

typedef struct s_game
{
	mlx_t *window;
	mlx_image_t *map_view;
	mlx_image_t *game_view;
	mlx_texture_t *texture;
	char **map;
	int map_width;
	int map_height;
	t_player player;
	uint32_t init_width;
	uint32_t init_height;
	uint32_t ceiling;
	uint32_t floor;

} t_game;

typedef struct s_all
{
	t_game *game_wrap;
	t_player *player_info;
} t_all;

#endif
