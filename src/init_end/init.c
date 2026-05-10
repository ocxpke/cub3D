#include "../../include/cub3d.h"

/**
 * @brief We set player orientation into the corresponding radians
 *
 * @note North/south logic is not inverted, optical ilussion.
 * @param player_info Struct containing all player info needed
 * @param map_info Struct containing all map info needed
 *
 * @return Void
 */
static inline void set_orientation(t_player *player_info, t_map *map_info)
{
	if (map_info->pstart_orientation == 'N')
		player_info->ang = RAD_90_DEG;
	else if (map_info->pstart_orientation == 'S')
		player_info->ang = RAD_270_DEG;
	else if (map_info->pstart_orientation == 'E')
		player_info->ang = RAD_180_DEG;
	else if (map_info->pstart_orientation == 'W')
		player_info->ang = RAD_360_DEG;
	else
		write(STDERR_FILENO, "Error at set_orientation", 24);
}

/**
 * @brief Just a function that checks all macros have the correct values
 *
 * @return Void
 */
inline void macro_checker(void)
{
	if (CUBSIZE <= 0 || (CUBSIZE & (CUBSIZE - 1)) != 0)
		return (write(STDERR_FILENO, "Check macro values\n", 19), exit(EXIT_FAILURE));
	if (FOV <= 0 || FOV > 360 || FPS <= 0 || HALF_FOV <= 0 || FOG <= 0 || PIX_COL <= 0 || NUM_TILES <= 0)
		return (write(STDERR_FILENO, "Check macro values\n", 19), exit(EXIT_FAILURE));
	if (!(CEILING_TEX_NUMBER > 0) || !(FLOOR_TEX_NUMBER > 0) || !(OBJ_NUMBER > 0))
		return (write(STDERR_FILENO, "Check macro values\n", 19), exit(EXIT_FAILURE));
	if (MOUSE_SENSIBILITY <= 0.0f || MOUSE_SENSIBILITY >= 0.5f)
		return (write(STDERR_FILENO, "Check macro values\n", 19), exit(EXIT_FAILURE));
	if (PLAYER_SPEED <= 0.0f || PLAYER_SPEED >= 1.0f)
		return (write(STDERR_FILENO, "Check macro values\n", 19), exit(EXIT_FAILURE));
	if (SENSIBILITY <= 0.0f)
		return (write(STDERR_FILENO, "Check macro values\n", 19), exit(EXIT_FAILURE));
	if (MAP_SIZE <= 0.0f || MAP_SIZE >= 1.0f)
		return (write(STDERR_FILENO, "Check macro values\n", 19), exit(EXIT_FAILURE));
	if (PLAYER_SIZE <= 0.0f || PLAYER_SIZE >= 1.0f)
		return (write(STDERR_FILENO, "Check macro values\n", 19), exit(EXIT_FAILURE));
}

/**
 * @brief Initialise every parameter needed
 *
 * @param game_wrap Represents the structure that contains all map
 * content and info needed
 * @param player_info Represents the strcuture that contains
 * all player info needed
 * @return Void
 */
void set_init_vals(t_game *game_wrap, t_player *player_info,
						  t_dpar *game_d)
{
	game_wrap->map = game_d->map_s->map;
	game_wrap->map_height = game_d->map_s->rows;
	game_wrap->map_width = game_d->map_s->cols;
	player_info->posx = game_d->map_s->pstart_x + HALF_POS;
	player_info->posy = game_d->map_s->pstart_y + HALF_POS;
	set_orientation(player_info, game_d->map_s);
	player_info->deltax = cos(player_info->ang) * PLAYER_SPEED;
	player_info->deltay = sin(player_info->ang) * PLAYER_SPEED;
	player_info->key_control.w_key = 0;
	player_info->key_control.s_key = 0;
	player_info->key_control.a_key = 0;
	player_info->key_control.d_key = 0;
	player_info->key_control.left_arrow = 0;
	player_info->key_control.right_arrow = 0;
}
