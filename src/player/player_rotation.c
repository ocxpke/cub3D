/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:22:07 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/03 15:45:46 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

inline void	rotate_player_left(t_player *player_info, float delta_time)
{
	player_info->p_moves = 1;
	player_info->ang -= 0.1 * delta_time;
	if (player_info->ang < 0)
		player_info->ang += (2 * PI);
	player_info->deltax = cos(player_info->ang) * PLAYER_SPEED;
	player_info->deltay = sin(player_info->ang) * PLAYER_SPEED;
}

inline void	rotate_player_right(t_player *player_info, float delta_time)
{
	player_info->p_moves = 1;
	player_info->ang += 0.1 * delta_time;
	if (player_info->ang > (2 * PI))
		player_info->ang -= (2 * PI);
	player_info->deltax = cos(player_info->ang) * PLAYER_SPEED;
	player_info->deltay = sin(player_info->ang) * PLAYER_SPEED;
}

void	player_key_rotation(t_game *game_wrap, t_player *player_info)
{
	float	delta_time;

	delta_time = game_wrap->window->delta_time * FPS * SENSIBILITY;
	if (player_info->key_control.left_arrow)
		rotate_player_left(player_info, delta_time);
	if (player_info->key_control.right_arrow)
		rotate_player_right(player_info, delta_time);
}
