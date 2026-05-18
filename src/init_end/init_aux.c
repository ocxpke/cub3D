/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:24:57 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/18 16:12:30 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void	init_values_obj(t_game *game_wrap, t_player *player_info,
		t_map *map_s, int i)
{
	game_wrap->obj_info[i].x_pos = map_s->keys_arr[i].k_posy + HALF_POS;
	game_wrap->obj_info[i].y_pos = map_s->keys_arr[i].k_posx + HALF_POS;
	game_wrap->obj_info[i].z_pos = 0;
	game_wrap->obj_info[i].state = 1;
	game_wrap->obj_info[i].type = OBJECT;
	game_wrap->obj_info[i].dist_to_player = dist(player_info->posx,
			player_info->posy, game_wrap->obj_info[i].x_pos,
			game_wrap->obj_info[i].y_pos);
	game_wrap->obj_ordered[i] = game_wrap->obj_info[i];
}

/**
 * @note We need to swap Rosa's And I cordinates axis
 */
void	load_all_sprites(t_game *game_wrap, t_player *player_info, t_dpar *pars)
{
	int		i;
	t_map	*map_s;

	map_s = pars->map_s;
	game_wrap->obj_info = (t_object_info *)ft_calloc(map_s->key_count,
			sizeof(t_object_info));
	if (!game_wrap->obj_info)
		exit(EXIT_FAILURE);
	game_wrap->obj_ordered = (t_object_info *)ft_calloc(map_s->key_count,
			sizeof(t_object_info));
	if (!game_wrap->obj_ordered)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < map_s->key_count)
	{
		init_values_obj(game_wrap, player_info, map_s, i);
		i++;
	}
	game_wrap->obj_num = map_s->key_count;
	order_objects(game_wrap);
	load_all_obj_textures(game_wrap);
}
