/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:00:27 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/05 19:01:18 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline uint32_t	color_of_ceil(t_game *game_wrap, t_raycast *rc,
		t_raycast_ceil_fl *rc_fl_cl)
{
	mlx_texture_t	*aux;

	aux = game_wrap->ceiling_tex.all_textures[rc->ceil_frame];
	if (game_wrap->ceiling_tex.type == IMAGE_TEXTURE)
		return (get_color_from_texture(aux, rc_fl_cl->ceil_fl_tex_x,
				rc_fl_cl->ceil_fl_tex_y, 0));
	else
		return (game_wrap->ceiling_tex.color);
}

static inline uint32_t	color_of_floor(t_game *game_wrap, t_raycast *rc,
		t_raycast_ceil_fl *rc_fl_cl)
{
	mlx_texture_t	*aux;

	aux = game_wrap->floor_tex.all_textures[rc->floor_frame];
	if (game_wrap->floor_tex.type == IMAGE_TEXTURE)
		return (get_color_from_texture(aux, rc_fl_cl->ceil_fl_tex_x,
				rc_fl_cl->ceil_fl_tex_y, 0));
	else
		return (game_wrap->floor_tex.color);
}

void	draw_ceil(t_game *game_wrap, t_raycast *rc, uint32_t x_trunc, int pixel)
{
	t_raycast_ceil_fl	*rc_cl;

	rc_cl = &(rc->ceil_fl_vars);
	rc_cl->ceil_fl_dy = (game_wrap->game_view->height / 2.0f) - pixel;
	if (rc_cl->ceil_fl_dy <= 0.0f)
		rc_cl->ceil_fl_dy = 1.0f;
	rc_cl->ceil_fl_straight_dist = (game_wrap->game_view->height / 2.0f)
		/ rc_cl->ceil_fl_dy;
	if (rc_cl->cos_corrected < 0.0001f)
		rc_cl->cos_corrected = 0.0001f;
	rc_cl->ceil_fl_true_dist = rc_cl->ceil_fl_straight_dist
		/ rc_cl->cos_corrected;
	rc_cl->ceil_fl_world_x = rc->player_posx_map + (rc_cl->cos_ray
			* rc_cl->ceil_fl_true_dist);
	rc_cl->ceil_fl_world_y = rc->player_posy_map + (rc_cl->sin_ray
			* rc_cl->ceil_fl_true_dist);
	rc_cl->ceil_fl_tex_x = (uint16_t)(rc_cl->ceil_fl_world_x * CUBSIZE)
		% CUBSIZE;
	rc_cl->ceil_fl_tex_y = (uint16_t)(rc_cl->ceil_fl_world_y * CUBSIZE)
		% CUBSIZE;
	mlx_put_pixel(game_wrap->game_view, x_trunc, pixel, color_of_ceil(game_wrap,
			rc, rc_cl));
}

void	draw_floor(t_game *game_wrap, t_raycast *rc, uint32_t x_trunc,
		int pixel)
{
	t_raycast_ceil_fl	*rc_fl;

	rc_fl = &(rc->ceil_fl_vars);
	rc_fl->ceil_fl_dy = pixel - (game_wrap->game_view->height / 2.0f);
	if (rc_fl->ceil_fl_dy <= 0.0f)
		rc_fl->ceil_fl_dy = 1.0f;
	rc_fl->ceil_fl_straight_dist = (game_wrap->game_view->height / 2.0f)
		/ rc_fl->ceil_fl_dy;
	if (rc_fl->cos_corrected < 0.0001f)
		rc_fl->cos_corrected = 0.0001f;
	rc_fl->ceil_fl_true_dist = rc_fl->ceil_fl_straight_dist
		/ rc_fl->cos_corrected;
	rc_fl->ceil_fl_world_x = rc->player_posx_map + (rc_fl->cos_ray
			* rc_fl->ceil_fl_true_dist);
	rc_fl->ceil_fl_world_y = rc->player_posy_map + (rc_fl->sin_ray
			* rc_fl->ceil_fl_true_dist);
	rc_fl->ceil_fl_tex_x = (uint16_t)(rc_fl->ceil_fl_world_x * CUBSIZE)
		% CUBSIZE;
	rc_fl->ceil_fl_tex_y = (uint16_t)(rc_fl->ceil_fl_world_y * CUBSIZE)
		% CUBSIZE;
	mlx_put_pixel(game_wrap->game_view, x_trunc, pixel,
		color_of_floor(game_wrap, rc, rc_fl));
}
