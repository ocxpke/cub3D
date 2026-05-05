/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:22:01 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/05 18:58:06 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Here we draw in the image map_view the player actual position as a dot
 *
 * @param game_wrap Represents the structure that contains all map content
 *and info needed
 * @param player_info Represents the strcuture that contains all player
 * info needed
 *
 * @return Void
 */
void	draw_player(t_game *game_wrap)
{
	int32_t	x;
	int32_t	y;
	int32_t	i;
	int32_t	j;

	x = game_wrap->map_view->width / 2;
	y = game_wrap->map_view->height / 2;
	i = -1 * game_wrap->player_size / 2;
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
static void	draw_direction(t_game *game_wrap, t_player *player_info)
{
	int	x;
	int	y;
	int	draw_x;
	int	draw_y;

	x = player_info->posX * CUBSIZE;
	y = player_info->posY * CUBSIZE;
	for (int i = 0; i < 70; i++)
	{
		draw_x = x + (i * cos(player_info->ang));
		draw_y = y + (i * sin(player_info->ang));
		if (draw_x >= 0 && draw_x < (int)game_wrap->map_view->width &&
			draw_y >= 0 && draw_y < (int)game_wrap->map_view->height)
		{
			fast_put_pixel(game_wrap->map_view, draw_x, draw_y, 0xFF0000FF);
		}
	}
}
*/
