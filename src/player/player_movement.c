/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:21:08 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/18 20:43:21 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void	collision_management(t_game *game_wrap,
		t_player *player_info, int next[2], float move[2])
{
	char	*cell_x;
	char	*cell_y;

	cell_x = &game_wrap->map[(int)player_info->posy][next[0]];
	cell_y = &game_wrap->map[next[1]][(int)player_info->posx];
	if (*cell_x != '1' && *cell_x != 'P')
		player_info->posx += move[0];
	if (*cell_y != '1' && *cell_y != 'P')
		player_info->posy += move[1];
}

static inline void	player_movement(t_game *game_wrap, t_player *player_info,
		float move_in_x, float move_in_y)
{
	float	margin_x;
	float	margin_y;
	int		next_x;
	int		next_y;

	margin_x = 0.25f;
	margin_y = 0.25;
	if (move_in_x < 0.0f)
		margin_x = -0.25f;
	else if (move_in_x == 0)
		margin_x = 0;
	if (move_in_y < 0)
		margin_y = -0.25f;
	else if (move_in_y == 0)
		margin_y = 0.0f;
	next_x = (int)(player_info->posx + move_in_x + margin_x);
	next_y = (int)(player_info->posy + move_in_y + margin_y);
	collision_management(game_wrap, player_info, (int [2]){next_x, next_y},
		(float [2]){move_in_x, move_in_y});
}

static inline void	calculate_player_speed(t_player *player_info,
		float *move_in_x, float *move_in_y, float delta_time)
{
	if (player_info->key_control.w_key)
	{
		player_info->p_moves = 1;
		*move_in_x += player_info->deltax * delta_time;
		*move_in_y += player_info->deltay * delta_time;
	}
	if (player_info->key_control.s_key)
	{
		player_info->p_moves = 1;
		*move_in_x += -1 * player_info->deltax * delta_time;
		*move_in_y += -1 * player_info->deltay * delta_time;
	}
	if (player_info->key_control.a_key)
	{
		player_info->p_moves = 1;
		*move_in_x += player_info->deltay * delta_time;
		*move_in_y += -1 * player_info->deltax * delta_time;
	}
	if (player_info->key_control.d_key)
	{
		player_info->p_moves = 1;
		*move_in_x += -1 * player_info->deltay * delta_time;
		*move_in_y += player_info->deltax * delta_time;
	}
}

static inline void	normalize_speed(t_player *player_info, float *move_in_x,
		float *move_in_y, float delta_time)
{
	float	pressed_key_speed;
	float	normal_speed;

	pressed_key_speed = sqrt(*move_in_x * *move_in_x + *move_in_y * *move_in_y);
	normal_speed = sqrt(player_info->deltax * player_info->deltax
			+ player_info->deltay * player_info->deltay) * delta_time;
	if (pressed_key_speed > normal_speed)
	{
		*move_in_x = (*move_in_x / pressed_key_speed) * normal_speed;
		*move_in_y = (*move_in_y / pressed_key_speed) * normal_speed;
	}
}

void	player_key_movement(t_game *game_wrap, t_player *player_info)
{
	float	delta_time;
	float	move_in_x;
	float	move_in_y;

	delta_time = game_wrap->window->delta_time * FPS * SENSIBILITY;
	move_in_x = 0;
	move_in_y = 0;
	calculate_player_speed(player_info, &move_in_x, &move_in_y, delta_time);
	normalize_speed(player_info, &move_in_x, &move_in_y, delta_time);
	player_movement(game_wrap, player_info, move_in_x, move_in_y);
}
