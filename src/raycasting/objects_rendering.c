/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:09:14 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/15 14:41:41 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void draw_object_pixel(t_game *game_wrap,
									 t_object_render *obj_render, int index)
{
	int t_num;

	t_num = game_wrap->obj_frame;
	obj_render->py = (int)obj_render->screen_y - obj_render->half_spr + index;
	if (obj_render->py < 0 || obj_render->py >= (int)game_wrap->game_view->height)
		return;
	obj_render->tex_y = (int)((float)index / obj_render->sprite_size * CUBSIZE);
	obj_render->color = get_color_from_texture(game_wrap->obj_textures[t_num],
											   obj_render->tex_x, obj_render->tex_y, 0);
	if (obj_render->color != IGNORE_COLOR)
	{
		obj_render->f_color = ((uint32_t)(((obj_render->color >> 24) & 0xFF) * obj_render->intensity) << 24);
		obj_render->f_color |= ((uint32_t)(((obj_render->color >> 16) & 0xFF) * obj_render->intensity) << 16);
		obj_render->f_color |= ((uint32_t)(((obj_render->color >> 8) & 0xFF) * obj_render->intensity) << 8);
		obj_render->f_color |= 0xFF;
		mlx_put_pixel(game_wrap->game_view, obj_render->px, obj_render->py,
					  obj_render->f_color);
	}
}

static inline int check_pixel_pos_wall_dist(t_game *game_wrap,
											t_player *player_info, t_object_render *obj_render, int game_depth)
{
	if ((obj_render->px < 0) || (obj_render->px >= (int)game_wrap->game_view->width))
		return (0);
	if (player_info->wall_distance[(int)(obj_render->px / game_wrap->col_gross)] < game_depth)
		return (0);
	return (1);
}

inline void represent_object(t_game *game_wrap, t_player *player_info,
							 t_object_render *obj_render)
{
	int i;
	int j;
	int game_depth;

	i = 0;
	game_depth = obj_render->depth * CUBSIZE;
	while (i < obj_render->sprite_size)
	{
		j = 0;
		obj_render->px = (int)obj_render->screen_x - obj_render->half_spr + i;
		if (check_pixel_pos_wall_dist(game_wrap, player_info, obj_render,
									  game_depth))
		{
			obj_render->tex_x = (int)(((float)i / obj_render->sprite_size * CUBSIZE));
			while (j < obj_render->sprite_size)
			{
				draw_object_pixel(game_wrap, obj_render, j);
				j++;
			}
		}
		i++;
	}
}

inline int calculate_obj_sprite_position(t_game *game_wrap,
										 t_player *player_info, t_object_render *obj_render, int index)
{
	obj_render->horizontal = -1 * obj_render->delta_x * obj_render->sine + obj_render->delta_y * obj_render->cosine;
	obj_render->angle_to_sprite = atan2f(obj_render->horizontal,
										 obj_render->depth);
	obj_render->sprite_size = (int)(game_wrap->game_view->height / obj_render->depth);
	obj_render->half_spr = obj_render->sprite_size / 2;
	obj_render->screen_x = (obj_render->angle_to_sprite / (ONE_DEGREE * HALF_FOV)) * (game_wrap->game_view->width / 2.0f) + (game_wrap->game_view->width / 2.0f);
	obj_render->screen_y = game_wrap->game_view->height / 2.0f + obj_render->sprite_size / 4.0f;
	obj_render->dist_ratio = (dist(player_info->posx, player_info->posy,
								   game_wrap->obj_ordered[index].x_pos,
								   game_wrap->obj_ordered[index].y_pos) *
							  CUBSIZE) /
							 MAX_PLAYER_VIEW_DIST;
	if (obj_render->dist_ratio > 1.0f)
		obj_render->dist_ratio = 1.0f;
	obj_render->intensity = 0.9f - (obj_render->dist_ratio * 0.8f);
	return (1);
}

inline int calculate_deltas_and_check_depth(t_game *game_wrap,
											t_player *player_info, t_object_render *obj_render, int index)
{
	obj_render->delta_x = game_wrap->obj_ordered[index].x_pos - player_info->posx;
	obj_render->delta_y = game_wrap->obj_ordered[index].y_pos - player_info->posy;
	if ((obj_render->delta_x > -0.2f && obj_render->delta_x < 0.2f) && (obj_render->delta_y > -0.2f && obj_render->delta_y < 0.2f))
	{
		game_wrap->obj_ordered[index].state = 0;
		game_wrap->obj_ordered[index].dist_to_player = 0;
		game_wrap->map[(int)game_wrap->obj_ordered[index].y_pos][(int)game_wrap->obj_ordered[index].x_pos] = '0' ;
		return (0);
	}

	obj_render->depth = obj_render->delta_x * obj_render->cosine + obj_render->delta_y * obj_render->sine;
	if (obj_render->depth <= 0.1f)
		return (0);
	return (1);
}
