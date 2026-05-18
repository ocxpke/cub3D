/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algorithym.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:28:02 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/18 16:07:52 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void	represent_line_simple(t_game *game, float current_p[2],
		float p_inc[2], uint32_t color)
{
	int	i;
	int	pixel_x;
	int	pixel_y;

	i = 0;
	while (i <= (int)p_inc[2])
	{
		pixel_x = (int)roundf(current_p[0]);
		pixel_y = (int)roundf(current_p[1]);
		if (pixel_x >= 0 && (uint32_t)pixel_x < game->map_view->width
			&& pixel_y >= 0 && (uint32_t)pixel_y < game->map_view->height)
		{
			mlx_put_pixel(game->map_view, pixel_x, pixel_y, color);
		}
		current_p[0] += p_inc[0];
		current_p[1] += p_inc[1];
		i++;
	}
}

/**
 * @note No la documento por q esto va a cambiar
 * @note dp[0] == dx || dp[1] == dy
 * @note p_inc[0] = x_inc ||  p_inc[1] = y_inc
 * @note current_p[0] == current_x || current_p[1] == current_y
 * @note p_inc[2] == steps
 */
// arreglar esta mierda
void	draw_line_simple(t_game *game, float p0[2], float p1[2], uint32_t color)
{
	float	dp[2];
	float	p_inc[3];
	float	current_p[2];

	dp[0] = p1[0] - p0[0];
	dp[1] = p1[1] - p0[1];
	if (fabs(dp[0]) > fabs(dp[1]))
		p_inc[2] = fabs(dp[0]);
	else
		p_inc[2] = fabs(dp[1]);
	if (p_inc[2] == 0)
		p_inc[2] = 1;
	p_inc[0] = dp[0] / p_inc[2];
	p_inc[1] = dp[1] / p_inc[2];
	current_p[0] = p0[0];
	current_p[1] = p0[1];
	represent_line_simple(game, current_p, p_inc, color);
}

static inline void	draw_ceil_wall_floor(t_game *game_wrap, t_raycast *rc,
		uint32_t x_trunc, uint16_t wall_hit_x)
{
	uint32_t	i;
	uint32_t	color_text;
	uint32_t	y0_trunc;
	uint32_t	y1_trunc;

	y0_trunc = (uint32_t)rc->wall_start;
	y1_trunc = (uint32_t)rc->wall_start + rc->wall_len;
	i = 0;
	while (i < game_wrap->game_view->height)
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
		i++;
	}
}

void	draw_player_view_line(t_game *game_wrap, t_raycast *rc,
		uint32_t x_trunc)
{
	uint16_t	wall_hit_x;

	wall_hit_x = (uint16_t)(CUBSIZE * rc->texture_x_hp);
	rc->ceil_fl_vars.ceil_fl_ang = rc->player_angle - rc->ray_angle;
	check_angle_bounds(game_wrap->const_values,
		&(rc->ceil_fl_vars.ceil_fl_ang));
	rc->ceil_fl_vars.cos_corrected = cos(rc->ceil_fl_vars.ceil_fl_ang);
	rc->ceil_fl_vars.cos_ray = cos(rc->ray_angle);
	rc->ceil_fl_vars.sin_ray = sin(rc->ray_angle);
	draw_ceil_wall_floor(game_wrap, rc, x_trunc, wall_hit_x);
}
