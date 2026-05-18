/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_view.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:27:07 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/18 20:37:43 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void	map_color_selec(t_game *game_wrap, int i, int j, int pp[2])
{
	if (game_wrap->map[i][j] == 'P' || game_wrap->map[i][j] == 'A')
		mlx_put_pixel(game_wrap->map_view, pp[0], pp[1], DOOR_COLOR);
	else if (game_wrap->map[i][j] == 'K')
		mlx_put_pixel(game_wrap->map_view, pp[0], pp[1], KEY_COLOR);
	else
		mlx_put_pixel(game_wrap->map_view, pp[0], pp[1], WALL_COLOR);
}

static inline void	draw_tile(t_game *game_wrap, int i, int j)
{
	int	px;
	int	py;
	int	z;
	int	q;

	z = 0;
	while (z < game_wrap->tile_size)
	{
		q = 0;
		while (q < game_wrap->tile_size)
		{
			px = (j * game_wrap->tile_size) - game_wrap->offset_x + q;
			py = (i * game_wrap->tile_size) - game_wrap->offset_y + z;
			if (px >= 0 && px < (int)game_wrap->map_view->width && py >= 0
				&& py < (int)game_wrap->map_view->height)
				map_color_selec(game_wrap, i, j, (int [2]){px, py});
			q++;
		}
		z++;
	}
}

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
	int	i;
	int	j;

	game_wrap->offset_x = (player_info->posx * game_wrap->tile_size)
		- (game_wrap->map_view->width / 2);
	game_wrap->offset_y = (player_info->posy * game_wrap->tile_size)
		- (game_wrap->map_view->height / 2);
	i = 0;
	while (i < game_wrap->map_height)
	{
		j = 0;
		while (j < game_wrap->map_width)
		{
			if (game_wrap->map[i][j] == '1' || game_wrap->map[i][j] == 'P'
				|| game_wrap->map[i][j] == 'K' || game_wrap->map[i][j] == 'A')
				draw_tile(game_wrap, i, j);
			j++;
		}
		i++;
	}
}
