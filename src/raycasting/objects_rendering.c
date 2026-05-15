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

static inline void represent_object(t_game *game_wrap, t_player *player_info, t_object_render *obj_render)
{
	int i = 0;

	while (i < obj_render->sprite_size)
	{
		int j = 0;
		obj_render->px = (int)obj_render->screen_x - obj_render->half_sprite + i;
		if (!(obj_render->px < 0 || obj_render->px >= (int)game_wrap->game_view->width))
		{
			if (!(player_info->wall_distance[obj_render->px / game_wrap->col_gross] < (obj_render->depth * CUBSIZE)))
			{
				obj_render->tex_x = (int)((float)i / obj_render->sprite_size * CUBSIZE);
				while (j < obj_render->sprite_size)
				{
					obj_render->py = (int)obj_render->screen_y - obj_render->half_sprite + j;
					if (!(obj_render->py < 0 || obj_render->py >= (int)game_wrap->game_view->height))
					{
						obj_render->tex_y = (int)((float)j / obj_render->sprite_size * CUBSIZE);
						obj_render->color = get_color_from_texture(game_wrap->obj_textures[game_wrap->obj_frame], obj_render->tex_x, obj_render->tex_y, 0);
						if (obj_render->color != IGNORE_COLOR)
						{
							obj_render->final_color = ((uint32_t)(((obj_render->color >> 24) & 0xFF) * obj_render->intensity) << 24);
							obj_render->final_color |= ((uint32_t)(((obj_render->color >> 16) & 0xFF) * obj_render->intensity) << 16);
							obj_render->final_color |= ((uint32_t)(((obj_render->color >> 8) & 0xFF) * obj_render->intensity) << 8);
							obj_render->final_color |= 0xFF;
							mlx_put_pixel(game_wrap->game_view, obj_render->px, obj_render->py, obj_render->final_color);
						}
					}
					j++;
				}
			}
		}
		i++;
	}
}

void draw_sprites(t_game *game_wrap, t_player *player_info)
{
	t_object_render obj_render;
	int i = 0;

	game_wrap->obj_frame = (get_time() / 150) % OBJ_NUMBER;
	obj_render.cosine = cos(player_info->ang);
	obj_render.sine = sin(player_info->ang);
	while (i < game_wrap->obj_num)
	{
		if (game_wrap->obj_info[i].state == 1)
		{
			obj_render.delta_x = game_wrap->obj_info[i].x_pos - player_info->posx;
			obj_render.delta_y = game_wrap->obj_info[i].y_pos - player_info->posy;
			obj_render.depth = obj_render.delta_x * obj_render.cosine + obj_render.delta_y * obj_render.sine;
			if (obj_render.depth > 0.1f)
			{
				obj_render.horizontal = -1 * obj_render.delta_x * obj_render.sine + obj_render.delta_y * obj_render.cosine;
				obj_render.angle_to_sprite = atan2f(obj_render.horizontal, obj_render.depth);
				obj_render.sprite_size = (int)(game_wrap->game_view->height / obj_render.depth);
				obj_render.half_sprite = obj_render.sprite_size / 2;
				obj_render.screen_x = (obj_render.angle_to_sprite / (ONE_DEGREE * HALF_FOV)) * (game_wrap->game_view->width / 2.0f) + (game_wrap->game_view->width / 2.0f);
				obj_render.screen_y = game_wrap->game_view->height / 2.0f + obj_render.sprite_size / 4.0f;
				obj_render.dist_ratio = (dist(player_info->posx, player_info->posy, game_wrap->obj_info[i].x_pos,
											  game_wrap->obj_info[i].y_pos) *
										 CUBSIZE) /
										MAX_PLAYER_VIEW_DIST;
				if (obj_render.dist_ratio > 1.0f)
					obj_render.dist_ratio = 1.0f;
				obj_render.intensity = 0.9f - (obj_render.dist_ratio * 0.8f);
				represent_object(game_wrap, player_info, &obj_render);
			}
		}
		i++;
	}
}
