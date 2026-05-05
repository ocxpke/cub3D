/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:40:24 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/05 19:05:31 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_UTILS_H
# define DRAW_UTILS_H

# include "cub3d.h"

void			draw_line_simple(t_game *game, float p0[2], float p1[2],
					uint32_t color);

void			draw_player_view_line(t_game *game, t_raycast *rc,
					uint32_t x_trunc);
uint32_t		get_color_from_texture(mlx_texture_t *texture, uint16_t x,
					uint16_t y, float dist);

void			draw_floor(t_game *game_wrap, t_raycast *rc, uint32_t x_trunc,
					int pixel);
void			draw_ceil(t_game *game_wrap, t_raycast *rc, uint32_t x_trunc,
					int pixel);

uint32_t		get_color_from_texture(mlx_texture_t *texture, uint16_t x,
					uint16_t y, float dist);
mlx_texture_t	*get_wall_texture(t_game *game, t_raycast *rc);

#endif
