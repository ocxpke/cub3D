/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algorithym.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:28:02 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/05 19:02:48 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @note No la documento por q esto va a cambiar
 */
// arreglar esta mierda
void	draw_line_simple(t_game *game, float p0[2], float p1[2], uint32_t color)
{
	float	dx;
	float	dy;
	float	steps;
	float	x_inc;
	float	y_inc;
	float	current_x;
	float	current_y;
	int		pixel_x;
	int		pixel_y;

	dx = p1[0] - p0[0]; // x1 - x0;
	dy = p1[1] - p0[1];
	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	// 1. PROTECCIÓN: Evitamos la división por cero si es un solo punto
	if (steps == 0)
		steps = 1;
	x_inc = dx / steps;
	y_inc = dy / steps;
	current_x = p0[0];
	current_y = p0[1];
	// Bucle para pintar
	for (int i = 0; i <= steps; i++)
	{
		// 3. PRECISIÓN: Redondeamos en lugar de truncar
		pixel_x = (int)roundf(current_x);
		pixel_y = (int)roundf(current_y);
		// Comprobación de límites (una sola vez)
		if (pixel_x >= 0 && (uint32_t)pixel_x < game->map_view->width
			&& pixel_y >= 0 && (uint32_t)pixel_y < game->map_view->height)
		{
			mlx_put_pixel(game->map_view, pixel_x, pixel_y, color);
		}
		current_x += x_inc;
		current_y += y_inc;
	}
}

void	draw_player_view_line(t_game *game_wrap, t_raycast *rc,
		uint32_t x_trunc)
{
	uint32_t	color_text;
	uint32_t	y0_trunc;
	uint32_t	y1_trunc;
	uint16_t	wall_hit_x;

	y0_trunc = (uint32_t)rc->wall_start;
	y1_trunc = (uint32_t)rc->wall_start + rc->wall_len;
	wall_hit_x = (uint16_t)(CUBSIZE * rc->texture_x_hp);
	rc->ceil_fl_vars.ceil_fl_ang = rc->player_angle - rc->ray_angle;
	check_angle_bounds(&(rc->ceil_fl_vars.ceil_fl_ang));
	rc->ceil_fl_vars.cos_corrected = cos(rc->ceil_fl_vars.ceil_fl_ang);
	rc->ceil_fl_vars.cos_ray = cos(rc->ray_angle);
	rc->ceil_fl_vars.sin_ray = sin(rc->ray_angle);
	for (uint32_t i = 0; i < game_wrap->game_view->height; i++)
	{
		if ((i >= y0_trunc) && (i <= y1_trunc))
		{
			color_text = get_color_from_texture(get_wall_texture(game_wrap, rc),
					wall_hit_x, (uint16_t)rc->texture_y_hp, rc->minor_distance);
			mlx_put_pixel(game_wrap->game_view, x_trunc, i, color_text);
			rc->texture_y_hp += rc->texture_steps;
		}
		else if (i < y0_trunc)
			draw_ceil(game_wrap, rc, x_trunc, i);
		else
			draw_floor(game_wrap, rc, x_trunc, i);
	}
}
