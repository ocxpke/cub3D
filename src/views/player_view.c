#include "../../include/cub3d.h"

/**
 * @brief Here we draw in the image map_view the player actual position as a dot
 *
 * @param game_wrap Represents the structure that contains all map content and info needed
 * @param player_info Represents the strcuture that contains all player info needed
 *
 * @return Void
 */
void draw_player(t_game *game_wrap, t_player *player_info)
{
	// Otra pedazo de mierda
	int map_cube_size;
	int horizontal_offset;
	int vertical_offset;

	//Este calculo se puede hacer a la hora de inicializar
	if (game_wrap->map_width >= game_wrap->map_height)
		map_cube_size = game_wrap->map_view->width / game_wrap->map_width;
	else
		map_cube_size = game_wrap->map_view->height / game_wrap->map_height;

	horizontal_offset = (game_wrap->map_view->width - (map_cube_size * game_wrap->map_width)) / 2;
	vertical_offset = (game_wrap->map_view->height - (map_cube_size * game_wrap->map_height)) / 2;
	int x = player_info->posX * map_cube_size;
	int y = player_info->posY * map_cube_size;

	for (int i = 0; i < PLAYER_PIX_SIZE; i++)
	{
		for (int j = 0; j < PLAYER_PIX_SIZE; j++)
		{
			int draw_x = x - 3 + j;
			int draw_y = y - 3 + i;
			if (draw_x >= 0 && draw_x < (int)game_wrap->map_view->width &&
				draw_y >= 0 && draw_y < (int)game_wrap->map_view->height)
				mlx_put_pixel(game_wrap->map_view, draw_x + horizontal_offset, draw_y + vertical_offset, 0xFF0000FF);
		}
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
