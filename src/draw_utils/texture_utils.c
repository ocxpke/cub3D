/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:02:32 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/18 16:07:28 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

uint32_t	get_color_from_texture(mlx_texture_t *texture, uint16_t x,
		uint16_t y, float dist)
{
	float		dist_ratio;
	float		intensity;
	uint32_t	base;
	uint32_t	final_color;

	if (!texture)
		return (0);
	dist_ratio = dist / (FOG * CUBSIZE);
	if (dist_ratio > 1.0f)
		dist_ratio = 1.0f;
	intensity = 0.9f - (dist_ratio * 0.8f);
	if (dist >= (FOG * CUBSIZE))
		intensity = 0;
	if (x >= texture->width || y >= texture->height)
		return (0);
	base = (x + (y * texture->width)) * 4;
	if (dist == 0)
		intensity = 1;
	final_color = ((uint32_t)(texture->pixels[base] * intensity) << 24);
	final_color |= ((uint32_t)(texture->pixels[base + 1] * intensity) << 16);
	final_color |= ((uint32_t)(texture->pixels[base + 2] * intensity) << 8);
	final_color |= 0xFF;
	return (final_color);
}

inline mlx_texture_t	*get_wall_texture(t_game *game, t_raycast *rc)
{
	t_const_vals	const_val;

	const_val = game->const_values;
	if (rc->coll_tex == DOOR_TEX)
		return (game->wall_text.door_tex);
	if (rc->hor_ver == 1)
	{
		if (rc->ray_angle > const_val.rad_180_deg
			&& rc->ray_angle < const_val.rad_360_deg)
			return (game->wall_text.south_tex);
		else
			return (game->wall_text.north_tex);
	}
	else
	{
		if (rc->ray_angle > const_val.rad_90_deg
			&& rc->ray_angle < const_val.rad_270_deg)
			return (game->wall_text.east_tex);
		else
			return (game->wall_text.west_tex);
	}
}
