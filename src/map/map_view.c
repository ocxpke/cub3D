#include "../../include/cub3d.h"

/**
 * @brief Here we calculate every pixel that needs to be drawed and draw the map grid
 *
 * @param game_wrap Represents the structure that contains all map content and info needed
 *
 * @return Void
 */
void draw_map(t_game *game_wrap, t_player *player_info)
{
	game_wrap->offset_x = (player_info->posX * game_wrap->tile_size) - (game_wrap->map_view->width / 2);
	game_wrap->offset_y = (player_info->posY * game_wrap->tile_size) - (game_wrap->map_view->height / 2);
	for (int i = 0; i < game_wrap->map_height; i++)
	{
		for (int j = 0; j < game_wrap->map_width; j++)
		{
			if (game_wrap->map[i][j] == '1')
			{
				for (int z = 0; z < game_wrap->tile_size; z++)
				{
					for (int q = 0; q < game_wrap->tile_size; q++)
					{
						int px = (j * game_wrap->tile_size) - game_wrap->offset_x + q;
						int py = (i * game_wrap->tile_size) - game_wrap->offset_y + z;
						if (px >= 0 && px < (int)game_wrap->map_view->width &&
							py >= 0 && py < (int)game_wrap->map_view->height)
							mlx_put_pixel(game_wrap->map_view, px, py, WALL_COLOR);
					}
				}
			}
		}
	}
}
