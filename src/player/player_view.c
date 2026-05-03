#include "../../include/cub3d.h"

/**
 * @brief Here we draw in the image map_view the player actual position as a dot
 *
 * @param game_wrap Represents the structure that contains all map content and info needed
 * @param player_info Represents the strcuture that contains all player info needed
 *
 * @return Void
 */
void draw_player(t_game *game_wrap)
{
	/**
	 * @note guardar en algun lado, y solo recalcular con resize
	 */
	int32_t x = game_wrap->map_view->width / 2;
	int32_t y = game_wrap->map_view->height / 2;
	int32_t i = -1 * game_wrap->player_size / 2;
	int32_t j;
	while (i < (game_wrap->player_size / 2))
	{
		j = -1 * game_wrap->player_size / 2;
		while (j < (game_wrap->player_size / 2))
		{
			mlx_put_pixel(game_wrap->map_view, x + j, y + i, PLAYER_COLOR);
			j++;
		}
		i++;
	}
}

/* @note This method is used to know where player is facing
static void draw_direction(t_game *game_wrap, t_player *player_info)
{
	int x = player_info->posX * CUBSIZE;
	int y = player_info->posY * CUBSIZE;

	for (int i = 0; i < 70; i++)
	{
		int draw_x = x + (i * cos(player_info->ang));
		int draw_y = y + (i * sin(player_info->ang));

		if (draw_x >= 0 && draw_x < (int)game_wrap->map_view->width &&
			draw_y >= 0 && draw_y < (int)game_wrap->map_view->height)
		{
			mlx_put_pixel(game_wrap->map_view, draw_x, draw_y, 0xFF0000FF);
		}
	}
}
*/
