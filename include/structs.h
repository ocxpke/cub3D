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
typedef struct s_player
{
	float posX;
	float posY;
	float dirX;
	float dirY;
	float ang;
} t_player;

typedef struct s_game
{
	mlx_t *mlx;
	mlx_image_t *map_view;
	mlx_image_t *game_view;
	char **map;
	int map_width;
	int map_height;
	t_player player;
} t_game;

typedef struct s_all
{
	t_game *game_wrap;
	t_player *player_info;
} t_all;

#endif
