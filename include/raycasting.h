/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:40:52 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/03 15:40:54 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

void	check_angle_bounds(float *angle);
void	draw_rays(t_game *game_wrap, t_player *player_info);
float dist(float x0, float y0, float x1, float y1);
void check_angle_bounds(float *angle);
void check_minor_distance(t_raycast *raycast);
void fix_fish_eye(t_player *player_info, t_raycast *raycast);
void check_horizontal_ray(t_game *game_wrap, t_raycast *rc);
void check_vertical_ray(t_game *game_wrap, t_raycast *rc);
void draw_sprites(t_game *game_wrap, t_player *player_info);

#endif
