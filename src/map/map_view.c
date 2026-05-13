/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_view.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:27:07 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/05 18:57:53 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Here we calculate every pixel that needs to be drawed and draw
 * the map grid
 *
 * @param game_wrap Represents the structure that contains all map content
 * and info needed
 *
 * @return Void
 */
void	draw_map(t_game *game_wrap, t_player *player_info)
{
	int	px;
	int	py;

	game_wrap->offset_x = (player_info->posx * game_wrap->tile_size)
		- (game_wrap->map_view->width / 2);
	game_wrap->offset_y = (player_info->posy * game_wrap->tile_size)
		- (game_wrap->map_view->height / 2);
	for (int i = 0; i < game_wrap->map_height; i++)
	{
		for (int j = 0; j < game_wrap->map_width; j++)
		{
			if (game_wrap->map[i][j] == '1' || game_wrap->map[i][j] == 'P')
			{
				for (int z = 0; z < game_wrap->tile_size; z++)
				{
					for (int q = 0; q < game_wrap->tile_size; q++)
					{
						px = (j * game_wrap->tile_size) - game_wrap->offset_x
							+ q;
						py = (i * game_wrap->tile_size) - game_wrap->offset_y
							+ z;
						if (px >= 0 && px < (int)game_wrap->map_view->width
							&& py >= 0 && py < (int)game_wrap->map_view->height)
						{
							if (game_wrap->map[i][j] == 'P')
								mlx_put_pixel(game_wrap->map_view, px, py,
									DOOR_COLOR);
							else
								mlx_put_pixel(game_wrap->map_view, px, py,
									WALL_COLOR);
						}
					}
				}
			}
		}
	}
}
