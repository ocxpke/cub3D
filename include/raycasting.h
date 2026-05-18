/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:40:52 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/18 16:20:11 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

void	order_objects(t_game *game_wrap);
void	check_angle_bounds(t_const_vals const_val, float *angle);
void	draw_rays(t_game *game_wrap, t_player *player_info);
float	dist(float x0, float y0, float x1, float y1);
void	check_minor_distance(t_raycast *raycast);
void	fix_fish_eye(t_const_vals const_val, t_player *player_info,
			t_raycast *raycast);
void	check_horizontal_ray(t_game *game_wrap, t_raycast *rc);
void	check_vertical_ray(t_game *game_wrap, t_raycast *rc);
void	draw_sprites(t_game *game_wrap, t_player *player_info);
int		calculate_deltas_and_check_depth(t_game *game_wrap,
			t_player *player_info, t_object_render *obj_render, int index);
int		calculate_obj_sprite_position(t_game *game_wrap,
			t_object_render *obj_render, int index);
void	represent_object(t_game *game_wrap, t_player *player_info,
			t_object_render *obj_render);
void	obj_is_alive(t_game *game_wrap, t_player *player_info,
			t_object_render *obj_render, int i);

#endif
