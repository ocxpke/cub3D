#include "../../include/cub3d.h"

/**
 * @brief Here we calculate every pixel that needs to be drawed and draw the map grid
 *
 * @param game_wrap Represents the structure that contains all map content and info needed
 *
 * @return Void
 */
void draw_map(t_game *game_wrap)
{
	int startX = 0, startY = 0;
	for (int i = 0; i < game_wrap->map_height; i++)
	{
		for (int j = 0; j < game_wrap->map_width; j++)
		{
			if (game_wrap->map[i][j] == '1')
			{
				startY = MAP_CUB_SIZE * i;
				startX = MAP_CUB_SIZE * j;
				for (int z = 0; z < MAP_CUB_SIZE; z++)
				{
					for (int q = 0; q < MAP_CUB_SIZE; q++)
					{
						if (((startX + q) >= 0) && ((startX + q) < (int)game_wrap->map_view->width) &&
							((startY + z) >= 0) && ((startY + z) < (int)game_wrap->map_view->height))
							mlx_put_pixel(game_wrap->map_view, startX + q, startY + z, 0x0000FFFF);
					}
				}
				draw_line_simple(game_wrap, startX, 0, startX, game_wrap->map_view->height, 0xFFFFFFFF, 0);
				draw_line_simple(game_wrap, 0,  startY, game_wrap->map_view->width, startY, 0xFFFFFFFF, 0);
			}
		}
	}
	// Last column and last row
	draw_line_simple(game_wrap, game_wrap->map_view->width, 0, game_wrap->map_view->width, game_wrap->map_view->height, 0xFFFFFFFF, 0);
	draw_line_simple(game_wrap, 0, game_wrap->map_view->height, game_wrap->map_view->width, game_wrap->map_view->height, 0xFFFFFFFF, 0);
}
