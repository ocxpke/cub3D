/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_func_raycast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:44:53 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/18 16:19:25 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

inline void	obj_is_alive(t_game *game_wrap, t_player *player_info,
		t_object_render *obj_render, int i)
{
	if (game_wrap->obj_ordered[i].state == 1)
	{
		if (player_info->p_moves)
			game_wrap->obj_ordered[i].dist_to_player = dist(player_info->posx,
					player_info->posy, game_wrap->obj_ordered[i].x_pos,
					game_wrap->obj_ordered[i].y_pos);
		if (calculate_deltas_and_check_depth(game_wrap, player_info, obj_render,
				i) && calculate_obj_sprite_position(game_wrap, obj_render, i))
			represent_object(game_wrap, player_info, obj_render);
	}
}
