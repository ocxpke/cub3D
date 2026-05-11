/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:09:14 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/11 19:09:16 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_sprites(t_game *game_wrap, t_player *player_info)
{
	t_object_info	obj;
	float			dx;
	float			dy;
	float			cs;
	float			sn;
	float			depth;
	float			horizontal;
	float			angle_to_sprite;
	float			screen_x;
	int				sprite_size;
	float			screen_y;
	int				half_s;
	float			dist_ratio;
	float			intensity;
	int				px;
	int				tex_x;
	int				py;
	int				tex_y;
	uint32_t		color;
	uint32_t		final_color;

	obj.obj_texture = mlx_load_png("./src/imgs/key_64/k_7.png");
	if (!obj.obj_texture)
		exit(1);
	obj.x_pos = 4.4f;
	obj.y_pos = 4.4f;
	dx = obj.x_pos - player_info->posx;
	dy = obj.y_pos - player_info->posy;
	cs = cos(player_info->ang);
	sn = sin(player_info->ang);
	depth = dx * cs + dy * sn;
	horizontal = -dx * sn + dy * cs;
	if (depth <= 0.1f)
		return ;
	angle_to_sprite = atan2f(horizontal, depth);
	screen_x = (angle_to_sprite / (ONE_DEGREE * HALF_FOV))
		* (game_wrap->game_view->width / 2.0f) + (game_wrap->game_view->width
			/ 2.0f);
	sprite_size = (int)(game_wrap->game_view->height / depth);
	screen_y = game_wrap->game_view->height / 2.0f + sprite_size / 4.0f;
	half_s = sprite_size / 2;
	dist_ratio = (dist(player_info->posx, player_info->posy, obj.x_pos,
				obj.y_pos) * CUBSIZE) / MAX_PLAYER_VIEW_DIST;
	if (dist_ratio > 1.0f)
		dist_ratio = 1.0f;
	intensity = 0.9f - (dist_ratio * 0.8f);
	for (int i = 0; i < sprite_size; i++)
	{
		px = (int)screen_x - half_s + i;
		if (px < 0 || px >= (int)game_wrap->game_view->width)
			continue ;
		if (player_info->wall_distance[px / game_wrap->col_gross] < (depth
				* CUBSIZE))
			continue ;
		tex_x = (int)((float)i / sprite_size * obj.obj_texture->width);
		for (int j = 0; j < sprite_size; j++)
		{
			py = (int)screen_y - half_s + j;
			if (py < 0 || py >= (int)game_wrap->game_view->height)
				continue ;
			tex_y = (int)((float)j / sprite_size * obj.obj_texture->height);
			color = get_color_from_texture(obj.obj_texture, tex_x, tex_y, 0);
			if (color != IGNORE_COLOR)
			{
				final_color = ((uint32_t)(((color >> 24) & 0xFF)
							* intensity) << 24);
				final_color |= ((uint32_t)(((color >> 16) & 0xFF)
							* intensity) << 16);
				final_color |= ((uint32_t)(((color >> 8) & 0xFF)
							* intensity) << 8);
				final_color |= 0xFF;
				mlx_put_pixel(game_wrap->game_view, px, py, final_color);
			}
		}
	}
}
