/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:40:43 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/18 16:06:20 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

void	rotate_player_left(t_player *player_info, float delta_time);
void	rotate_player_right(t_player *player_info, float delta_time);
void	draw_player(t_game *game_wrap);
void	player_key_movement(t_game *game_wrap, t_player *player_info);
void	player_key_rotation(t_game *game_wrap, t_player *player_info);
#endif
