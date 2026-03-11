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
	int map_cube_size;
	int horizontal_offset;
	int vertical_offset;

	if (game_wrap->map_width >= game_wrap->map_height)
		map_cube_size = game_wrap->map_view->width / game_wrap->map_width;
	else
		map_cube_size = game_wrap->map_view->height / game_wrap->map_height;
	horizontal_offset = (game_wrap->map_view->width - (map_cube_size * game_wrap->map_width)) / 2;
	vertical_offset = (game_wrap->map_view->height - (map_cube_size * game_wrap->map_height)) / 2;
	int startX = 0, startY = 0;
	for (int i = 0; i < game_wrap->map_height; i++)
	{
		for (int j = 0; j < game_wrap->map_width; j++)
		{
			if (game_wrap->map[i][j] == '1')
			{
				startY = map_cube_size * i;
				startX = map_cube_size * j;
				for (int z = 0; z < map_cube_size; z++)
				{
					for (int q = 0; q < map_cube_size; q++)
					{
						if (((horizontal_offset + startX + q) >= 0) && ((horizontal_offset + startX + q) < (int)game_wrap->map_view->width) &&
							((vertical_offset + startY + z) >= 0) && ((vertical_offset + startY + z) < (int)game_wrap->map_view->height))
							mlx_put_pixel(game_wrap->map_view, horizontal_offset + startX + q, vertical_offset + startY + z, 0x0000FFFF);
					}
					draw_line_simple(game_wrap, horizontal_offset + startX, vertical_offset, horizontal_offset + startX, game_wrap->map_view->height - vertical_offset, 0xFFFFFFFF, 0);
				}
				draw_line_simple(game_wrap, horizontal_offset, vertical_offset + startY, game_wrap->map_view->width - horizontal_offset, vertical_offset + startY, 0xFFFFFFFF, 0);
			}
		}
	}
	// Last column and last row
	draw_line_simple(game_wrap, game_wrap->map_view->width - horizontal_offset, vertical_offset, game_wrap->map_view->width - horizontal_offset, game_wrap->map_view->height - vertical_offset, 0xFFFFFFFF, 0);
	draw_line_simple(game_wrap, horizontal_offset, game_wrap->map_view->height - vertical_offset, game_wrap->map_view->width - horizontal_offset, game_wrap->map_view->height - vertical_offset, 0xFFFFFFFF, 0);
}
