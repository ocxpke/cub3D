/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:18:03 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/13 17:48:10 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Just a function to initialize values for the raycast struct
 *
 * @param player_info Struct that has all player usefull information
 * @param raycast All variables that we need to initialize are here
 *
 * @return Void
 */
static inline void	init_raycast_values(t_player *player_info,
		t_raycast *raycast)
{
	raycast->player_angle = player_info->ang;
	raycast->player_posx_cube = player_info->posx * CUBSIZE;
	raycast->player_posy_cube = player_info->posy * CUBSIZE;
	raycast->player_posx_map = player_info->posx;
	raycast->player_posy_map = player_info->posy;
	raycast->horizontal_dist = 100000;
	raycast->vertical_dist = 100000;
	raycast->ray_ct = 0;
	raycast->ray_x = 0;
	raycast->ray_y = 0;
	raycast->ray_x_offset = 0;
	raycast->ray_y_offset = 0;
	raycast->ceil_frame = (get_time() / 150) % CEILING_TEX_NUMBER;
	raycast->floor_frame = (get_time() / 150) % FLOOR_TEX_NUMBER;
}

/**
 * @brief We swap the x position to fix the mirror effect that ocurrs when
 * display a texture
 *
 * @param raycast Struct containing all raycaster previously calculated values
 *
 * @return Void
 */
static inline void	invert_texture_x(t_raycast *raycast)
{
	if (raycast->horizontal_dist <= raycast->vertical_dist)
	{
		if (raycast->ray_angle < PI)
			raycast->texture_x_hp = 1.0f - raycast->texture_x_hp;
	}
	else
	{
		if (raycast->ray_angle > RAD_90_DEG && raycast->ray_angle < RAD_270_DEG)
			raycast->texture_x_hp = 1.0f - raycast->texture_x_hp;
	}
}

/**
 * @brief Where all the graphic magic takes place here we will calculate ray
 * col gross and draw a pixel col of each colum color per gross.
 *
 * @param game_wrap Struct containing game most important information
 * @param raycast Struct containing all raycaster previously calculated values
 *
 * @return Void
 */
static inline void	draw_frame_cols(t_game *game_wrap, t_raycast *raycast)
{
	raycast->wall_len = (CUBSIZE * game_wrap->game_view->height)
		/ raycast->minor_distance;
	raycast->save_tex_y = 0;
	raycast->texture_steps = (float)CUBSIZE / raycast->wall_len;
	if (raycast->wall_len > game_wrap->game_view->height)
	{
		raycast->save_tex_y = ((raycast->wall_len
					- game_wrap->game_view->height) / 2)
			* raycast->texture_steps;
		raycast->wall_len = game_wrap->game_view->height;
	}
	raycast->wall_start = (game_wrap->game_view->height - raycast->wall_len)
		/ 2;
	raycast->iter_gross = 0;
	invert_texture_x(raycast);
	while (raycast->iter_gross < game_wrap->col_gross)
	{
		raycast->texture_y_hp = raycast->save_tex_y;
		draw_player_view_line(game_wrap, raycast, (uint32_t)(raycast->ray_ct
				* game_wrap->col_gross) + raycast->iter_gross);
		raycast->iter_gross++;
	}
}

/**
 * @brief The raycaster itself. Here we calculate what player sees,
 * the player view field is 60º,and we create rays on that player view field
 * and calculate where they hit to display a vertical wall.
 *
 * @note Needs to be sliced and optimized
 * @note This documentation will be updated
 * @note How palyer will see something that is too far away?
 *
 * @param game_wrap Represents the structure that contains all map content
 * and info needed
 * @param player_info Represents the strcuture that contains all
 * player info needed
 *
 * @return Void
 */
void	draw_rays(t_game *game_wrap, t_player *player_info)
{
	t_raycast	raycast;

	init_raycast_values(player_info, &raycast);
	raycast.ray_angle = player_info->ang - (ONE_DEGREE * HALF_FOV);
	check_angle_bounds(&raycast.ray_angle);
	while (raycast.ray_ct < game_wrap->pixels_cols)
	{
		check_horizontal_ray(game_wrap, &raycast);
		check_vertical_ray(game_wrap, &raycast);
		check_minor_distance(&raycast);
		raycast.texture_x_hp -= floor(raycast.texture_x_hp);
		fix_fish_eye(player_info, &raycast);
		draw_frame_cols(game_wrap, &raycast);
		draw_line_simple(game_wrap, (float []){game_wrap->map_view->width / 2,
			game_wrap->map_view->height / 2}, (float []){((raycast.ray_x
					/ CUBSIZE) * game_wrap->tile_size) - game_wrap->offset_x,
			(raycast.ray_y / CUBSIZE) * game_wrap->tile_size
			- game_wrap->offset_y}, RAY_COLOR);
		raycast.ray_angle += ((ONE_DEGREE * FOV) / game_wrap->pixels_cols);
		check_angle_bounds(&raycast.ray_angle);
		raycast.ray_ct++;
	}
}
